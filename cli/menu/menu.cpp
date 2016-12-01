#include "menu.hpp"

using namespace std;
using namespace Functions;

void CLIs::Menu::setOffsets( unsigned int& offset_x, unsigned int& offset_y ) {
	// Déclaration des variables utiles
	unsigned int len, width = this->m_header.size();

	// On parcours les valeurs, et on récupère la largeur maximale
	for( const auto& choice : this->m_choices ) {
		len = choice.size();

		// Si on dépasse la largeur maximale trouvée
		if( width < len ) {
			// Alors on la stocke en tant que tel
			width = len;
		}
	}

	// On récupère les offsets à appliquer pour centrer le niveau
	CLI::setOffsets( width, this->m_choices.size() + 1, offset_x, offset_y );
}

/****
	Permet d'afficher un menu interactif, utilisant les touches flechees, Entree et Esc
	 Demande:
		 - Le texte a afficher en haut du menu
		 - Les choix
	Retourne:
		- Entier >= 1 representant le choix
		- 0 si aucun choix n'a ete fait
****/
CLIs::Menu::Menu( string header, vector<string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color ) : m_header( header ), m_choices( this->m_choices ) {
	// Initialisation des variables nécessaires
	unsigned int exit = 0, offset_x = 0, offset_y = 0;
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
		cout << "=== %s ===" << endl;

		for( unsigned int i = 0; i < this->m_choices.size() ; i++ ) {
			// Afficher les choix
			if( this->m_choice == i + 1) {
				// Si le choix sélectionné correspond au texte à afficher, on met la couleur d'en-tête souhaitée
				cli.setColor( selection_color );
			} else {
				// Sinon on affiche la couleur de fond
				cli.setColor( back_color );
			}

			// On se place là où doit être cette ligne
			cli.moveCursor( offset_y + i + 1, offset_x );

			// On affiche le texte
			cout << this->m_choices[ i ] << endl;
		}

		// On récupère la touche appuyée
		key = cli.getKey();

		switch( key ) {
			case Keys::Key::ArrowUp:
				// Si la flèche du haut est appuyée, passer au choix précédent
				if( this->m_choice > 1 )
					this->m_choice--;
				break;
			case Keys::Key::ArrowDown:
				// Si la flèche du bas est appuyée, passer au choix suivant
				if( this->m_choice < this->m_choices.size() )
					this->m_choice++;
				break;
			case Keys::Key::Escape:
				// Si la touche Esc est appuyée, passer le choix à 0
				this->m_choice = 0;
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