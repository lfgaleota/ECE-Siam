#include "cli.hpp"

using namespace Functions;

/****
	Destructeur de la classe, permet de remettre à zéro la mise en forme de la console et effacer l'écran pour quitter proprement.
****/
CLI::~CLI() {
	this->resetColor();
	this->clearScreen();
}

/****
	Permet d'effectuer une pause silencieuse dans la console.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::pause() {
	std::cin.ignore( std::cin.rdbuf()->in_avail() );
	std::getchar();
}

#if defined( ANSI_TERM )

/****
	Constructeur de la classe.
****/
CLI::CLI() {}

/****
	Permet d'effacer la sortie de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen()  {
	// Codes ANSI pour efface la sortie du terminal
	const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";

	// Ces codes ANSI, pour une raison quelconque, font que tout texte suivant directement a son 1er caractère recopié avec un espace avant, ceci avant son affichage.
	write( STDOUT_FILENO, CLEAR_SCREE_ANSI, 12 );

	// Ce write évite le problème, mais affiche une ligne vide.
	write( STDOUT_FILENO, " \n", 0);

	// REMARQUE: On retrouve le même comportement avec les commandes natives cls ou clear. Il est possible que ces commandes utilisent les mêmes codes ANSI.
}

#elif defined( WIN )

/****
	Constructeur de la classe.
****/
CLI::CLI() {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &this->attributes );
}

/****
	Permet d'effacer la sortie de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen() {
	HANDLE						hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	DWORD						count;
	DWORD						cellCount;
	COORD						homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if( hStdOut == INVALID_HANDLE_VALUE ) return;

	// Obtenir la taille du buffer
	if( !GetConsoleScreenBufferInfo( hStdOut, &csbi  )) return;
	cellCount = (DWORD) ( csbi.dwSize.X * csbi.dwSize.Y );

	// Remplir le buffer avec des espaces
	if( !FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		) ) return;

	// Remplir le buffer les attributs et couleurs actuelles
	if( !FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		) ) return;

	// Déplacer le curseur à sa position initiale
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

#elif defined( UNIX )

/****
	Constructeur de la classe.
****/
CLI::CLI() {}

/****
	Permet d'effacer la sortie de la console. Dépend du système
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::clearScreen() {
	if( !cur_term ) {

		int result;
		setupterm( NULL, STDOUT_FILENO, & result );
		if( result <= 0 ) return;

	}

	putp( tigetstr( "clear" ) );
}

/****
	Permet de récupérer la taille de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Largeur de la console (par référence)
		- Hauteur de la console (par référence)
****/
void CLI::getSize( unsigned int& width, unsigned int& height ) {
	// On récupère la taille
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, & w );

	width = w.ws_row;
	height = w.ws_col;
}

/****
	Permet de récupérer les coordonnées permettant de centrer un élément de taille donnée dans la console. Dépend du système.
	Demande:
		- Largeur de l'élément
		- Hauteur de l'élément
	Retourne:
		- Colonne où placer l'élément (par référence)
		- Ligne où palcer l'élément (par référence)
****/
void CLI::setOffsets( unsigned int width, unsigned int height, unsigned int& u_offset_x, unsigned int& u_offset_y ) {
	int offset_x, offset_y;

	// On récupère la taille
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, & w );

	// On calcule les offsets de manière à centrer l'élément, sans déborder sur les côtés
	offset_x = ( ( w.ws_row - 1 ) - width ) / 2;
	offset_y = ( ( w.ws_col - 1 ) - height ) / 2;

	u_offset_x = ( offset_x >= 0 ? (unsigned) offset_x : 0 );
	u_offset_y = ( offset_y >= 0 ? (unsigned) offset_y : 0 );
}

#endif

#if defined( UNIX ) || defined( ANSI_TERM )

/****
	Permet de déplacer le curseur à des coordonnées précise. Dépend du système.
	Demande:
		- Colonne
		- Ligne
	Retourne:
		- Rien
****/
void CLI::moveCursor( unsigned int line, unsigned int column ) {
	std::cout << "\033[" << line + 1 << ";" << column + 1 << "H";
}

/****
	Permet de changer la couleur d'avant-plan et d'arrière-plan de la console. Dépend du système.
	Demande:
		- Ensemble de couleur
	Retourne:
		- Rien
****/
void CLI::setColor( unsigned char color ) {
	std::string colorCodes;

	if( color & ( BACKGROUND_INTENSITY | FOREGROUND_INTENSITY ) ) {
		colorCodes += "\33[1m"; // Intensity
	}

	if( color & FOREGROUND_RED && color & FOREGROUND_GREEN && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[37m"; // White
	} else if( color & FOREGROUND_RED && color & FOREGROUND_GREEN ) {
		colorCodes += "\33[33m"; // Yellow
	} else if( color & FOREGROUND_RED && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[35m"; // Magenta
	} else if( color & FOREGROUND_GREEN && color & FOREGROUND_BLUE ) {
		colorCodes += "\33[36m"; // Cyan
	} else if( color & FOREGROUND_RED ) {
		colorCodes += "\33[31m"; // Red
	} else if( color & FOREGROUND_GREEN ) {
		colorCodes += "\33[32m"; // Green
	} else if( color & FOREGROUND_BLUE ) {
		colorCodes += "\33[34m"; // Blue
	} else {
		colorCodes += "\33[30m"; // Black
	}

	if( color & BACKGROUND_RED && color & BACKGROUND_GREEN && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[47m"; // White
	} else if( color & BACKGROUND_RED && color & BACKGROUND_GREEN ) {
		colorCodes += "\33[43m"; // Yellow
	} else if( color & BACKGROUND_RED && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[45m"; // Magenta
	} else if( color & BACKGROUND_GREEN && color & BACKGROUND_BLUE ) {
		colorCodes += "\33[46m"; // Cyan
	} else if( color & BACKGROUND_RED ) {
		colorCodes += "\33[41m"; // Red
	} else if( color & BACKGROUND_GREEN ) {
		colorCodes += "\33[42m"; // Green
	} else if( color & BACKGROUND_BLUE ) {
		colorCodes += "\33[44m"; // Blue
	} else {
		colorCodes += "\33[40m"; // Black
	}

	std::cout << colorCodes;
}

/****
	Permet de réinitialiser la mise en forme de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::resetColor() {
	std::cout << "\033[0m";
}

#elif defined( WIN )

/****
	Permet de déplacer le curseur à des coordonnées précise. Dépend du système.
	Demande:
		- Colonne
		- Ligne
	Retourne:
		- Rien
****/
void CLI::moveCursor( unsigned int line, unsigned int column ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if( hConsole == INVALID_HANDLE_VALUE ) return;

	// Définition d'une structure coordonéees
	COORD destCoords;
	destCoords.X = column;
	destCoords.Y = line;

	// Définition de la nouvelle position du curseur
	SetConsoleCursorPosition( hConsole, destCoords );
}

/****
	Permet de changer la couleur d'avant-plan et d'arrière-plan de la console. Dépend du système.
	Demande:
		- Ensemble de couleur
	Retourne:
		- Rien
****/
void CLI::setColor( unsigned char color ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Appliquation des nouveaux attributs de couleur
	SetConsoleTextAttribute( hConsole, (WORD) color );
}

/****
	Permet de réinitialiser la mise en forme de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Rien
****/
void CLI::resetColor() {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Restauration des attributs initiaux
	SetConsoleTextAttribute( hConsole, this->attributes.wAttributes );
}

/****
	Permet de récupérer la taille de la console. Dépend du système.
	Demande:
		- Rien
	Retourne:
		- Largeur de la console (par référence)
		- Hauteur de la console (par référence)
****/
void CLI::getSize( unsigned int& width, unsigned int& height ) {
	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Définition des variables utiles
	CONSOLE_SCREEN_BUFFER_INFO consoleInfos;

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &consoleInfos );

	/*
	 * consoleInfos.srWindow.Right - consoleInfos.srWindow.Left donne le nombre de colonnes en partant de 0
	 * consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top  donne le nombre de lignes en partant de 0
	 */
	width = consoleInfos.srWindow.Right - consoleInfos.srWindow.Left + 1;
	height = consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top + 1;
}

/****
	Permet de récupérer les coordonnées permettant de centrer un élément de taille donnée dans la console. Dépend du système.
	Demande:
		- Largeur de l'élément
		- Hauteur de l'élément
	Retourne:
		- Colonne où placer l'élément (par référence)
		- Ligne où palcer l'élément (par référence)
****/
void CLI::setOffsets( unsigned int width, unsigned int height, unsigned int& u_offset_x, unsigned int& u_offset_y ) {
	int offset_x, offset_y;

	// Récupération d'un handle vers la console
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	// Définition des variables utiles
	CONSOLE_SCREEN_BUFFER_INFO consoleInfos;

	// Récupération des attributs actuels de la console
	GetConsoleScreenBufferInfo( hConsole, &consoleInfos );

	/*
	 * consoleInfos.srWindow.Right - consoleInfos.srWindow.Left donne le nombre de colonnes en partant de 0
	 * consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top  donne le nombre de lignes en partant de 0
	 */

	// On calcule les offsets de manière à centrer l'élément, sans déborder sur les côtés
	offset_x = ( ( consoleInfos.srWindow.Right - consoleInfos.srWindow.Left + 1 ) -  width ) / 2;
	offset_y = ( ( consoleInfos.srWindow.Bottom - consoleInfos.srWindow.Top + 1 ) - height ) / 2 ;

	u_offset_x = ( offset_x >= 0 ? (unsigned) offset_x : 0 );
	u_offset_y = ( offset_y >= 0 ? (unsigned) offset_y : 0 );
}

#endif
