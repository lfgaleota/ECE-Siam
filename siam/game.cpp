#include "inc/game.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

void Game::display() { //displays the matrix
	auto& matrix = this->m_board.getBoard(); //get a read access to the matrix
	Siam::Object* elem = nullptr; //we'll need this to fill the blank spots

	for( unsigned int j = 0; j < matrix.size(); j++ ) { //browse
		for( unsigned int i = 0; i < matrix[ j ].size(); i++ ) {
			elem = matrix[ i ][ j ];

			if( elem != nullptr ) { //different types of display function of the spot content
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
				switch( elem->getDirection() ) { //display the direction of a piece
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

void Game::addOnBoard() { //add a piece to the board
	unsigned int x, y;
	char direction;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl; //displays instructions
		cin >> x; //gets the requirements
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			switch( direction ) { //effectively adds the piece and orients it
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
		} catch( Siam::exceptions::invalid_move e ) { //shielding
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

void Game::removeFromBoard() { //remove a piece from the board
	unsigned int x, y;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl; //displays instructions
		cin >> x;
		cin >> y;

		try { //don't ask man, it works
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "You do not own this piece !" );
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

void Game::moveOnBoard() { //make a move on the board
	unsigned int x, y;
	char direction;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl; //display instructions
		cin >> x;
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //check if you can move the piece
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //shields it
			switch( direction ) { //else moves the piece according to the instructions
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
				// we ejected a spot
				if( obj->getType() == Siam::Objects::Types::Type::Mountain ) {
					// if it's a mountain increment his mountaincount
					this->m_currentPlayer->incrementMountainsCount();
					// And of course destroy the mountain
					delete obj;
				} else {
					// else put the piece back in the right stack
					for( auto& loopplayer : this->m_players ) {
						if( loopplayer.getAnimalChosen() == obj->getType() )
							loopplayer.stockPiece( obj );
					}
				}
			}
		} catch( Siam::exceptions::invalid_move e ) { //shielding
			std::cerr << e.what() << std::endl;
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void Game::orientOnBoard() { //reorient a piece on the board
	unsigned int x, y;
	char direction;

	for( bool loop = true; loop; ) {
		loop = false;

		cout << "A quelles coordonnees ?" << endl; //displays instructions
		cin >> x;
		cin >> y;
		cout << "Dans quelle direction ?(h/b/g/d)" << endl;
		cin >> direction;

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //just orients a piece according to the player wishes
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //checks if u are allowed to do it first
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
		} catch( Siam::exceptions::invalid_move e ) { //shielding
			std::cerr << e.what() << std::endl;
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			std::cerr << "Empty space" << std::endl;
			loop = true;
		}
	}
}

void Game::playerTurn() { //unfolding of a turn
	int choice;

	if( this->m_currentPlayer == this->m_players.end() )
		this->m_currentPlayer = this->m_players.begin();

	display();

	std::cout << "Vous etes " << this->m_currentPlayer->getName() << "." << std::endl; //display information
	std::cout << "Vous avez pousse " << this->m_currentPlayer->getMountainsCount() << " montagnes." << std::endl;

	do {
		cout << "vos possibilites sont : " << endl; //display instructions
		cout << "   1. Ajouter une nouvelle piece sur le terrain" << endl;
		cout << "   2. Enlever une piece du terrain" << endl;
		cout << "   3. Bouger une piece sur le terrain" << endl;
		cout << "   4. Changer l'orientation d'une piece" << endl;
		cout << endl;
		cout << "quel est votre choix ?";
		cin >> choice;

		switch( choice ) { //what type of turn would you like to take ?
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

bool Game::isFinished() { //if a moutain was pushed out, then the game is finished
	return ( this->m_board.getMountainsCount() > 0 );
}

void Game::victory() { //WIN
	std::vector<Siam::Player>::iterator winingPlayer = this->m_players.begin();

	for( auto it = this->m_players.begin(); it != this->m_players.end(); it++ ) {
		if( it->getMountainsCount() > it->getMountainsCount() )
			winingPlayer = it;
	}

	std::cout << "Bravo " << winingPlayer->getName() << ", tu as gagne!" << std::endl;
}

Game::Game( vector<Player> players ) { //that's how it goes down
	Siam::Matrix board = Siam::Matrix(); //initialize the matrix

	this->m_players = players; //and the players
	this->m_currentPlayer = players.begin(); //first player "selected"

	while( isFinished() ) //while nobody won
		playerTurn(); //turns
	victory(); //if you won -> victory

	for( auto& player : this->m_players )
		player.removeRemainingObjects(); //delete everything in the stacks
}
