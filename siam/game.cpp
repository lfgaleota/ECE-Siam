#include "inc/game.hpp"
#include "inc/ui/games/CLI.hpp"

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

			this->m_ui->addPiece( obj );
		} catch( Siam::exceptions::invalid_move e ) { //shielding
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_currentPlayer->stockPiece( obj );
		} catch( Siam::exceptions::stack_empty e ) {
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
		} catch( Siam::exceptions::invalid_move e ) {
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::stack_full e ) {
			this->m_ui->showError( e.what() );
			loop = true;
			if( obj != nullptr )
				this->m_board.add( obj, x, y );
		} catch( Siam::exceptions::invalid_object_type e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::moveOnBoard() { //make a move on the board
	unsigned int x, y;
	Direction dir;
	Siam::Object* obj = nullptr;
	map<const Object*, pair<unsigned int, unsigned int>> movements;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, &dir );

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //check if you can move the piece
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //shields it

			obj = this->m_board.move( x, y, dir, movements );
			this->m_ui->movePiece( movements );

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
			this->m_ui->showError( e.what() );
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::orientOnBoard() { //reorient a piece on the board
	unsigned int x, y;
	Direction dir, oldDir;

	for( bool loop = true; loop; ) {
		loop = false;

		this->m_ui->getPlayerCoords( x, y, &dir );

		try {
			if( this->m_board.getType( x, y ) != this->m_currentPlayer->getAnimalChosen() ) //just orients a piece according to the player wishes
				throw Siam::exceptions::invalid_move( "Piece not to the player" ); //checks if u are allowed to do it first

			oldDir = this->m_board.getDirection( x, y );

			this->m_board.orient( x, y, dir );

			this->m_ui->orientPiece( this->m_board.getObject( x, y ), oldDir );
		} catch( Siam::exceptions::invalid_move e ) { //shielding
			this->m_ui->showError( e.what() );
			loop = true;
		} catch( Siam::exceptions::invalid_object_type e ) {
			this->m_ui->showError( "Empty space" );
			loop = true;
		}
	}
}

void Game::playerTurn() { //unfolding of a turn
	if( this->m_currentPlayer == this->m_players.end() )
		this->m_currentPlayer = this->m_players.begin();

	this->m_ui->playerTurnBegin( *this->m_currentPlayer );

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

	this->m_ui->playerTurnEnd( *this->m_currentPlayer );

	this->m_currentPlayer = next( this->m_currentPlayer );
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

	this->m_ui->victory( *winingPlayer );
}

Game::Game( vector<Player> players ) { //that's how it goes down
	Siam::Matrix board = Siam::Matrix(); //initialize the matrix

	this->m_ui = new Siam::UI::Games::CLI( board.getBoard(), players );

	this->m_players = players; //and the players
	this->m_currentPlayer = this->m_players.begin(); //first player "selected"

	try {
		while( isFinished() ) //while nobody won
			playerTurn(); //turns
		victory(); //if you won -> victory
	} catch( exceptions::exit_game e ) {
		this->m_ui->showError( "Exiting" );
	}

	for( auto& player : this->m_players )
		player.removeRemainingObjects(); //delete everything in the stacks
	
	delete this->m_ui;
}
