#include <iostream>
#include <vector>
#include "siam/inc/matrix.hpp"
#include "siam/inc/player.hpp"

using namespace std;

void display( Siam::Matrix& board ) {
	auto& matrix = board.getBoard();
	Siam::Object* elem = nullptr;

	for( unsigned int j = 0; j < matrix.size(); j++ ) {
		for( unsigned int i = 0; i < matrix[ j ].size(); i++ ) {
			elem = matrix[ i ][ j ];

			if( elem != nullptr ) {
				switch( elem->getType() ) {
					case Siam::Objects::Types::Type::Mountain:
						std::cout << "M";
						break;
					case Siam::Objects::Types::Type::Rhinoceros:
						std::cout << "R";
						break;
					case Siam::Objects::Types::Type::Elephant:
						std::cout << "E";
						break;
					case Siam::Objects::Types::Type::Object:
						break;
					case Siam::Objects::Types::Type::Entity:
						break;
				}
				switch( elem->getDirection() ) {
					case Siam::Matrixs::Direction::Left:
						std::cout << "<";
						break;
					case Siam::Matrixs::Direction::Right:
						std::cout << ">";
						break;
					case Siam::Matrixs::Direction::Up:
						std::cout << "/";
						break;
					case Siam::Matrixs::Direction::Down:
						std::cout << "\\";
						break;
				}
			} else {
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

Siam::Player initPlayer( Siam::Player* player ) {
	bool choix;
	Siam::Objects::Types::Type animal;
	std::string name;

	cout << "joueur entrez votre nom : ";
	cin >> name;

	cout << "vous etes plutot du genre a jouer les elephants " << name << " non ?" << endl;
	cout << "0:OUI 1:NON" << endl;
	cin >> choix;

	return Siam::Player( name,
	                     ( choix ? Siam::Objects::Types::Type::Elephant : Siam::Objects::Types::Type::Rhinoceros ) );
}

void ajout( Siam::Matrix& board, Siam::Player& player ) {
	unsigned int x, y;
	char direction;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl;
		cin >> x;
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			switch( direction ) {
				case 'g' :
					obj = player.retrievePiece();
					board.add( obj, x, y );
					board.orient( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					obj = player.retrievePiece();
					board.add( obj, x, y );
					board.orient( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					obj = player.retrievePiece();
					board.add( obj, x, y );
					board.orient( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					obj = player.retrievePiece();
					board.add( obj, x, y );
					board.orient( x, y, Siam::Matrixs::Direction::Down );
					break;

				default:
					loop = true;
					break;
			}
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				player.stockPiece( obj );
		} catch( Siam::exceptions::stack_empty e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
		}
	}
}

void remove( Siam::Matrix& board, Siam::Player& player ) {
	unsigned int x, y;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl;
		cin >> x;
		cin >> y;

		try {
			if( board.getType( x, y ) != player.getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			obj = board.remove( x, y );
			player.stockPiece( obj );
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				board.add( obj, x, y );
		} catch( Siam::exceptions::stack_full e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				board.add( obj, x, y );
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void move( Siam::Matrix& board, std::vector<Siam::Player>& players, Siam::Player& player ) {
	unsigned int x, y;
	char direction;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl;
		cin >> x;
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			if( board.getType( x, y ) != player.getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			switch( direction ) {
				case 'g' :
					obj = board.move( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					obj = board.move( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					obj = board.move( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					obj = board.move( x, y, Siam::Matrixs::Direction::Down );
					break;

				default:
					loop = true;
					break;
			}

			if( obj != nullptr ) {
				// On a ejecté une case!
				if( obj->getType() == Siam::Objects::Types::Type::Mountain ) {
					// Si c'est une montagne, on incrémente le compteur du joueur actuel
					player.incrementMountainsCount();
					// Et on détruit la montagne, bien sûr!
					delete obj;
				} else {
					// Sinon on remet la pièce dans la pile de pièces du joueur
					for( auto& loopplayer : players ) {
						if( loopplayer.getAnimalChosen() == obj->getType() )
							loopplayer.stockPiece( obj );
					}
				}
			}
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void orient( Siam::Matrix& board, Siam::Player& player ) {
	unsigned int x, y;
	char direction;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl;
		cin >> x;
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			if( board.getType( x, y ) != player.getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			switch( direction ) {
				case 'g' :
					board.orient( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					board.orient( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					board.orient( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					board.orient( x, y, Siam::Matrixs::Direction::Down );
					break;

				default:
					loop = true;
					break;
			}
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void tour( Siam::Matrix& board, std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer ) {
	int choice;

	if( currentPlayer == players.end() )
		currentPlayer = players.begin();

	display( board );

	std::cout << "Vous etes " << currentPlayer->getName() << "." << std::endl;
	std::cout << "Vous avez pousse " << currentPlayer->getMountainsCount() << " montagnes." << std::endl;

	do {
		cout << "vos possibilites sont : " << endl;
		cout << "   1. Ajouter une nouvelle piece sur le terrain" << endl;
		cout << "   2. Enlever une piece du terrain" << endl;
		cout << "   3. Bouger une piece sur le terrain" << endl;
		cout << "   4. Changer l'orientation d'une piece" << endl;
		cout << endl;
		cout << "quel est votre choix ?";
		cin >> choice;

		switch( choice ) {
			case 1:
				//add
				ajout( board, *currentPlayer );
				break;
			case 2:
				//remove
				remove( board, *currentPlayer );
				break;
			case 3:
				//move
				move( board, players, *currentPlayer );
				break;
			case 4:
				//orient
				orient( board, *currentPlayer );
				break;
		}
	} while( choice < 1 || choice > 4 );

	currentPlayer++;
}

bool isFinished( Siam::Matrix& board ) {
	return ( board.getMountainsCount() > 0 );
}

void victory( std::vector<Siam::Player>& players ) {
	std::vector<Siam::Player>::iterator winingPlayer = players.begin();

	for( auto it = players.begin(); it != players.end(); it++ ) {
		if( it->getMountainsCount() > it->getMountainsCount() )
			winingPlayer = it;
	}

	std::cout << "Bravo " << winingPlayer->getName() << ", tu as gagne!" << std::endl;
}

int main() {
	std::vector<Siam::Player> players;
	players.push_back( Siam::Player( "Louis-Félix", Siam::Objects::Types::Type::Rhinoceros ) );
	players.push_back( Siam::Player( "Romain", Siam::Objects::Types::Type::Elephant ) );

	std::vector<Siam::Player>::iterator currentPlayer = players.begin();

	Siam::Matrix board = Siam::Matrix(); //on initialise le terrain de jeu !

	while( isFinished( board ) )
		tour( board, players, currentPlayer );
	victory( players );

	return 0;
}
