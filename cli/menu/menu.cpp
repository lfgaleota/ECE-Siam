#include "menu.hpp"

using namespace std;
using namespace Functions;

void CLIs::Menu::setOffsets( int& offset_x, int& offset_y ) {
	// Déclaration des variables utiles
	unsigned int i;
	int len, width = this->header.size();

	// On parcours les valeurs, et on récupère la largeur maximale
	for( const auto& choice : this->choices ) {
		len = choice.size();

		// Si on dépasse la largeur maximale trouvée
		if( width < len ) {
			// Alors on la stocke en tant que tel
			width = len;
		}
	}

	// On récupère les offsets à appliquer pour centrer le niveau
	CLI::setOffsets( width, choices.size() + 1, offset_x, offset_y );
}

/****
	Permet d'afficher un menu interactif, utilisant les touches flechees, Entree et Esc
	 Demande:
		 - Le texte a afficher en haut du menu (header_text)
		 - Le nombre des choix (this->choices_c)
		 - Un tableau de chaines de caracteres, representant les choix (this->choices)
	Retourne:
		- Entier >= 1 representant le choix
		- 0 si aucun choix n'a ete fait
****/
CLI::Menu::Menu( string header, vector<string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color ) : m_header( header ), m_choices( this->choices ) {
	// Initialisation des variables nécessaires
	unsigned int exit = 0;
	int offset_x = 0, offset_y = 0;
	Keys::Key key;
	CLI cli = CLI();

	// On récupère les offsets pour centrer le menu
	setOffsets( offset_x, offset_y );

	while( exit == 0 ) {
		// On met la couleur de fond souhaitée
		cli.setColor( back_color );

		// On efface la sortie de la console
		cli.clearScreen();

		// On met la couleur d'en-tête souhaitée
		cli.setColor( header_color );
		// On se place en haut, en tenant compte des offsets
		cli.moveCursor( offset_y, offset_x );
		// On affiche l'en-tête
		printf( "=== %s ===", header_text );

		for( i = 0; i < this->choices_c ; i++ ) {
			// Afficher les choix
			if( this->choice == i + 1) {
				// Si le choix sélectionné correspond au texte à afficher, on met la couleur d'en-tête souhaitée
				cli.setColor( selection_color );
			} else {
				// Sinon on affiche la couleur de fond
				cli.setColor( back_color );
			}

			// On se place là où doit être cette ligne
			cli.moveCursor( offset_y + i + 1, offset_x );

			// On affiche le texte
			printf( "%s", this->choices[ i ] );
		}

		// On récupère la touche appuyée
		key = cli.getKey();

		switch( key ) {
			case Keys::Key::ArrowUp:
				// Si la flèche du haut est appuyée, passer au choix précédent
				if( this->choice > 1) this->choice--;
				break;
			case Keys::Key::ArrowDown:
				// Si la flèche du bas est appuyée, passer au choix suivant
				if( this->choice < this->choices_c ) this->choice++;
				break;
			case Keys::Key::Escape:
				// Si la touche Esc est appuyée, passer le choix à 0
				this->choice = 0;
			case Keys::Key::Enter:
				// Si la touche Entrée ou Esc est appuyée, quitter la boucle du menu
				exit = 1;
				break;
			default:
				break;
		}

	}

	// On rétablie les couleurs d'origines
	cli.resetColor();

	// On efface l'écran pour nettoyer les artefacts
	cli.clearScreen();
}

unsigned int CLIs::Menu::getChoice() const {
	return this->m_choice;
}