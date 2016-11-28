#include "inc/game.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

void Game::display() {
	auto& matrix = this->m_board.getBoard();
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

void Game::addOnBoard() {
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
					obj = this->m_currentPlayer->retrievePiece();
					this->m_board.add( obj, x, y );
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					obj = this->m_currentPlayer->retrievePiece();
					this->m_board.add( obj, x, y );
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					obj = this->m_currentPlayer->retrievePiece();
					this->m_board.add( obj, x, y );
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					obj = this->m_currentPlayer->retrievePiece();
					this->m_board.add( obj, x, y );
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Down );
					break;

				default:
					loop = true;
					break;
			}
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				this->m_currentPlayer->stockPiece( obj );
		} catch( Siam::exceptions::stack_empty e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
		}
	}
}

void Game::removeFromBoard() {
	unsigned int x, y;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl;
		cin >> x;
		cin >> y;

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			obj = this->m_board.remove( x, y );
			this->m_currentPlayer->stockPiece( obj );
		} catch( Siam::exceptions::invalid_move e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::stack_full e ) {
			std::cerr << e.what() << std::endl;
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void Game::moveOnBoard() {
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
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			switch( direction ) {
				case 'g' :
					obj = this->m_board.move( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					obj = this->m_board.move( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					obj = this->m_board.move( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					obj = this->m_board.move( x, y, Siam::Matrixs::Direction::Down );
					break;

				default:
					loop = true;
					break;
			}

			if( obj != nullptr ) {
				// On a ejecté une case!
				if( obj->getType() == Siam::Objects::Types::Type::Mountain ) {
					// Si c'est une montagne, on incrémente le compteur du joueur actuel
					this->m_currentPlayer->incrementMountainsCount();
					// Et on détruit la montagne, bien sûr!
					delete obj;
				} else {
					// Sinon on remet la pièce dans la pile de pièces du joueur
					for( auto& loopplayer : this->m_players ) {
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

void Game::orientOnBoard() {
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
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "Piece not to the player" );
			switch( direction ) {
				case 'g' :
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Left );
					break;

				case 'd' :
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Right );
					break;

				case 'h' :
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Up );
					break;

				case 'b' :
					this->m_board.orient( x, y, Siam::Matrixs::Direction::Down );
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

void Game::playerTurn() {
	int choice;

	if( this->m_currentPlayer == this->m_players.end() )
		this->m_currentPlayer = this->m_players.begin();

	display();

	std::cout << "Vous etes " << this->m_currentPlayer->getName() << "." << std::endl;
	std::cout << "Vous avez pousse " << this->m_currentPlayer->getMountainsCount() << " montagnes." << std::endl;

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
				addOnBoard();
				break;
			case 2:
				//remove
				removeFromBoard();
				break;
			case 3:
				//move
				moveOnBoard();
				break;
			case 4:
				//orient
				orientOnBoard();
				break;
		}
	} while( choice < 1 || choice > 4 );

	this->m_currentPlayer++;
}

bool Game::isFinished() {
	return ( this->m_board.getMountainsCount() > 0 );
}

void Game::victory() {
	std::vector<Siam::Player>::iterator winingPlayer = this->m_players.begin();

	for( auto it = this->m_players.begin(); it != this->m_players.end(); it++ ) {
		if( it->getMountainsCount() > it->getMountainsCount() )
			winingPlayer = it;
	}

	std::cout << "Bravo " << winingPlayer->getName() << ", tu as gagne!" << std::endl;
}

Game::Game( vector<Player> players ) {
	Siam::Matrix board = Siam::Matrix();
	
	this->m_players = players;
	this->m_currentPlayer = players.begin();

	while( isFinished() )
		playerTurn();
	victory();

	for( auto& player : this->m_players )
		player.removeRemainingObjects();
}