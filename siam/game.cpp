#include "inc/game.hpp"
#include "inc/ui/games/gamecliui.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;

void Game::addOnBoard() { //add a piece to the board
	unsigned int x = 0, y = 0;
	Direction dir;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, &dir );

		try {
			//effectively adds the piece and orients it
			obj = this->m_currentPlayer->retrievePiece();
			this->m_board.add( obj, x, y );
			this->m_board.orient( x, y, dir );

			this->m_ui->addPiece( obj, x, y );
		} catch( Siam::exceptions::invalid_move& e ) { //shielding
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_currentPlayer->stockPiece( obj );
		} catch( Siam::exceptions::stack_empty& e ) {
			this->m_ui->showError( e.what() );
			loop = true;
		}
	}
}

void Game::removeFromBoard() { //remove a piece from the board
	unsigned int x, y;
	Siam::Object* obj = nullptr;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, nullptr );

		try { //don't ask man, it works
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() )
				throw Siam::exceptions::invalid_move( "You do not own this piece !" );
			obj = this->m_board.remove( x, y );
			this->m_currentPlayer->stockPiece( obj );

			this->m_ui->removePiece( obj );
		} catch( Siam::exceptions::invalid_move& e ) {
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::stack_full& e ) {
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::invalid_object_type& e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::moveOnBoard() { //make a move on the board
	unsigned int x, y;
	Direction dir;
	Siam::Object* ejectedobj = nullptr, *winingobj = nullptr;
	map<const Object*, pair<unsigned int, unsigned int>> movements;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, &dir );

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //check if you can move the piece
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //shields it

			ejectedobj = this->m_board.move( x, y, dir, movements );
			this->m_ui->movePiece( movements );

			if( ejectedobj != nullptr ) {
				// we ejected a spot
				if( ejectedobj->getType() == Siam::Objects::Types::Type::Mountain ) {
					// we try to detect which player gets the point
					winingobj = this->m_board.getWiningObject( x, y, dir );
					if( winingobj != nullptr ) {
						for( auto& loopplayer : this->m_players ) {
							if( loopplayer.getAnimalChosen() == winingobj->getType() ) {
								// if it's a mountain increment his mountaincount
								loopplayer.incrementMountainsCount();
								// Also the game is ended!
								this->won = true;
							}
						}
					} else {
						cout << "No wining obj";
						getchar();
					}
					// And of course destroy the mountain
					delete ejectedobj;
				} else {
					// else put the piece back in the right stack
					for( auto& loopplayer : this->m_players ) {
						if( loopplayer.getAnimalChosen() == ejectedobj->getType() )
							loopplayer.stockPiece( ejectedobj );
					}
				}
			}
		} catch( Siam::exceptions::invalid_move& e ) { //shielding
			this->m_ui->showError( e.what() );
			loop = true;
		} catch( Siam::exceptions::invalid_object_type& e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::orientOnBoard() { //reorient a piece on the board
	unsigned int x, y;
	Direction dir;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, &dir );

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //just orients a piece according to the player wishes
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //checks if u are allowed to do it first

			this->m_board.orient( x, y, dir );

			this->m_ui->orientPiece( this->m_board.getObject( x, y ) );
		} catch( Siam::exceptions::invalid_move& e ) { //shielding
			this->m_ui->showError( e.what() );
			loop = true;
		} catch( Siam::exceptions::invalid_object_type& e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::playerTurn() { //unfolding of a turn
	if( this->m_currentPlayer == this->m_players.end() )
		this->m_currentPlayer = this->m_players.begin();

	this->m_ui->playerTurnBegin( *this->m_currentPlayer );

	for( bool loop = true; loop; ) {
		loop = false;

		try {
			switch( this->m_ui->getPlayerAction( *this->m_currentPlayer ) ) { //what type of turn would you like to take ?
				case Players::Add:
					//add
					addOnBoard();
					break;
				case Players::Remove:
					//remove
					removeFromBoard();
					break;
				case Players::Move:
					//move
					moveOnBoard();
					break;
				case Players::Orient:
					//orient
					orientOnBoard();
					break;
				default:
					break;
			}
		} catch( exceptions::cancel_action ) {
			loop = true;
		}
	}

	this->m_ui->playerTurnEnd( *this->m_currentPlayer );

	this->m_currentPlayer = next( this->m_currentPlayer );
}

void Game::victory() { //WIN
	std::vector<Siam::Player>::iterator winingPlayer = this->m_players.begin();

	for( auto it = this->m_players.begin(); it != this->m_players.end(); it++ ) {
		if( it->getMountainsCount() > winingPlayer->getMountainsCount() )
			winingPlayer = it;
	}

	this->m_ui->victory( *winingPlayer );
}

Game::Game( vector<Player> players ) { //that's how it goes down
	this->m_players = players; //and the players
	this->m_currentPlayer = this->m_players.begin(); //first player "selected"

	this->m_ui = new Siam::UI::Games::CLI( this->m_board.getBoard(), this->m_players, this->m_currentPlayer );

	try {
		while( !this->won ) //while nobody won
			playerTurn(); //turns
		victory(); //if you won -> victory
		Sleep(2000);
	} catch( exceptions::exit_game e ) {
		this->m_ui->showError( "Exiting" );
	}

	for( auto& player : this->m_players )
		player.removeRemainingObjects(); //delete everything in the stacks

	delete this->m_ui;
}
