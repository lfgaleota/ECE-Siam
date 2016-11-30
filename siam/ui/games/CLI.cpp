#include "../../inc/ui/games/CLI.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;
using namespace Siam::UI::Games;

CLI::CLI( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players ) : Game( board, players ) {
	cli = Functions::CLI();
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
}

void CLI::showError( string msg ) {
	cerr << msg << endl;
}

void CLI::displayMatrix() {
	Object* elem = nullptr; //we'll need this to fill the blank spots

	for( unsigned int j = 0; j < this->m_board.size(); j++ ) { //browse
		for( unsigned int i = 0; i < this->m_board[ j ].size(); i++ ) {
			elem = this->m_board[ i ][ j ];

			if( elem != nullptr ) { //different types of display function of the spot content
				switch( elem->getType() ) {
					case Types::Type::Mountain:
						cout << "M";
						break;
					case Types::Type::Rhinoceros:
						cout << "R";
						break;
					case Types::Type::Elephant:
						cout << "E";
						break;
					case Types::Type::Object:
						break;
					case Types::Type::Entity:
						break;
				}
				switch( elem->getDirection() ) { //display the direction of a piece
					case Direction::Left:
						cout << "<";
						break;
					case Direction::Right:
						cout << ">";
						break;
					case Direction::Up:
						cout << "/";
						break;
					case Direction::Down:
						cout << "\\";
						break;
				}
			} else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void CLI::displayPlayers() {
	std::string carac = "";
	unsigned int offset_x, offset_y, width, height, pos_y = 0;

	cli.getSize( width, height );
	cli.setOffsets( 1, 5, offset_x, offset_y );

	for( const Player& player : this->m_players ) {
		switch( player.getAnimalChosen() ) {
			case Types::Type::Elephant:
				carac = "E";
				pos_y = 1;
				break;
			case Types::Type::Rhinoceros:
				carac = "R";
				pos_y = width - 2;
				break;
			default:
				throw exceptions::invalid_object_type();
		}

		for( unsigned int i = 0; i < 5; i++ ) {
			if( player.getRemainingObjects() - i >= 0 ) {
				cli.moveCursor( offset_y + i, pos_y );
				std::cout << carac;
			}
		}
	}
}

void CLI::getPlayerCoords( unsigned int& x, unsigned int& y, Direction* dir ) {
	char direction;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl; //displays instructions
		cin >> x; //gets the requirements
		cin >> y;

		if( dir != nullptr ) {
			cout << "Dans quelle direction ?(h/b/g/d)" << endl;
			cin >> direction;

			switch( direction ) {
				case 'g' :
					*dir = Direction::Left;
					break;

				case 'd' :
					*dir = Direction::Right;
					break;

				case 'h' :
					*dir = Direction::Up;
					break;

				case 'b' :
					*dir = Direction::Down;
					break;

				default:
					loop = true;
					break;
			}
		}
	}
}

void CLI::addPiece( const Object* ) {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
}

void CLI::removePiece( const Object* ) {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
}

void CLI::movePiece( map<const Object*, pair<unsigned int, unsigned int>>& movements ) {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
}

void CLI::orientPiece( const Object*, Direction oldDir ) {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
}

void CLI::playerTurnBegin( Siam::Player& player ) {
	std::cout << "Vous etes " << player.getName() << "." << std::endl; //display information
	std::cout << "Vous avez pousse " << player.getMountainsCount() << " montagnes." << std::endl;
}

void CLI::playerTurnEnd( Siam::Player& player ) {

}

Players::Action CLI::getPlayerAction( Siam::Player& player ) {
	int choice;

	while( true ) {
		cout << "vos possibilites sont : " << endl; //display instructions
		cout << "   1. Ajouter une nouvelle piece sur le terrain" << endl;
		cout << "   2. Enlever une piece du terrain" << endl;
		cout << "   3. Bouger une piece sur le terrain" << endl;
		cout << "   4. Changer l'orientation d'une piece" << endl;
		cout << "   5. Ne rien faire" << endl;
		cout << endl;
		cout << "quel est votre choix ?";
		cin >> choice;

		switch( choice ) { //what type of turn would you like to take ?
			case 1:
				return Players::Action::Add;
			case 2:
				return Players::Action::Remove;
			case 3:
				return Players::Action::Move;
			case 4:
				return Players::Action::Orient;
			case 5:
				return Players::Action::Nothing;
			default:
				break;
		}
	};
}

void CLI::victory( Siam::Player& player ) {
	std::cout << "Bravo " << player.getName() << ", tu as gagne!" << std::endl;
}