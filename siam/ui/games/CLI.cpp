#include "../../inc/ui/games/CLI.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;
using namespace Siam::UI::Games;

CLI::CLI( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer ) : Game( board, players, currentPlayer ) {
	cli = Functions::CLI();
	fmod = Siam::UI::Audio::FMOD();
	loadDisplayMatrix();
	display();
}

void CLI::showError( string msg ) {
	cerr << msg << endl;
}

void CLI::display() {
	cli.clearScreen();
	displayMatrix();
	displayPlayers();
	displayActions();
}

void CLI::showPiece( Object* elem ) {
	if( elem != nullptr ) { //different types of display function of the spot content
		switch( elem->getType()) {
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
		if( elem->getType() == Types::Type::Mountain )
			cout << " ";
		else {
			switch( elem->getDirection()) { //display the direction of a piece
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
		}
	} else {
		cout << "  ";
	}
}

void CLI::displayMatrix() {
	Object* elem = nullptr; //we'll need this to fill the blank spots
	unsigned int x = 0, y = 0;

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), x, y );

	for( unsigned int j = 0; j < this->m_displayMatrix.size(); j++ ) {
		cli.moveCursor( y + j, x );
		cli.setColor( FOREGROUND_RED | FOREGROUND_INTENSITY );
		cout << m_displayMatrix[ j ];
	}

	cli.resetColor();

	for( unsigned int j = 0; j < this->m_board.size(); j++ ) { //browse
		for( unsigned int i = 0; i < this->m_board[ j ].size(); i++ ) {
			elem = this->m_board[ i ][ j ];

			cli.moveCursor( y + j * 2 + 4, x + i * 5 + 2 );
			cli.setColor( FOREGROUND_GREEN | FOREGROUND_INTENSITY );

			showPiece( elem );
		}
	}

	cli.resetColor();
}

void CLI::highlightSelectedPiece( unsigned int x, unsigned int y, unsigned char color ) {
	unsigned int offsetX = 0, offsetY = 0;

	cli.setColor( color );

	cli.setOffsets( this->m_displayMatrix.begin()->size(), this->m_displayMatrix.size(), offsetX, offsetY );
	cli.moveCursor( offsetY + y * 2 + 4, offsetX + x * 5 + 2 );

	showPiece( this->m_board[ x ][ y ] );

	cli.moveCursor( offsetY + y * 2 + 4 + 1, offsetX + x * 5 + 2 );
	cout << "__";

	cli.resetColor();
}

void CLI::displayPlayers() {
	std::string carac = "";
	unsigned int offset_x, offset_y, width, height, pos_y = 0;

	cli.getSize( width, height );

	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
	if( this->m_currentPlayer == this->m_players.begin() )
		cli.moveCursor( 0, 0 );
	else
		cli.moveCursor( 0, width / 2 );
	for( unsigned int i = 0; i < width / 2; i++ )
		cout << " ";
	cli.resetColor();

	for( unsigned int i = 0; i < this->m_players.size(); i++ ) {
		cli.moveCursor( 0, ( !( i % 2 ) ? 0 : width / 2 ) );
		if( &this->m_players[ i ] == &( *this->m_currentPlayer ) )
			cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
		cout << this->m_players[ i ].getName();
		cli.resetColor();
	}

	cli.setOffsets( 1, 5, offset_x, offset_y );

	for( unsigned int i = 0; i < this->m_players.size(); i++ ) {
		switch( this->m_players[ i ].getAnimalChosen() ) {
			case Types::Type::Elephant:
				cli.setColor( BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
				carac = "E";
				break;
			case Types::Type::Rhinoceros:
				cli.setColor( BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
				carac = "R";
				break;
			default:
				throw exceptions::invalid_object_type();
		}

		if( i == 0 )
			pos_y = 1;
		else
			pos_y = width - 2;

		for( unsigned int j = 0; j < this->m_players[ i ].getRemainingObjects(); j++ ) {
			cli.moveCursor( offset_y + j, pos_y );
			std::cout << carac;
		}

		cli.resetColor();
	}
}

void CLI::displayActions() {
	unsigned int width, height;
	string menu[] = {
			"Ajouter",
	        "Retirer",
	        "Deplacer",
	        "Orienter",
	        "Passer"
	};
	cli.getSize( width, height );

	cli.moveCursor( height - 1, 0 );
	for( unsigned int i = 0; i < 5; i++ ) {
		cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED| BACKGROUND_GREEN | BACKGROUND_INTENSITY );
		cout << i + 1;
		cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED| BACKGROUND_GREEN );
		cout << menu[ i ];
	}

	cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED| BACKGROUND_GREEN | BACKGROUND_INTENSITY );
	cout << 0;
	cli.setColor( BACKGROUND_BLUE | BACKGROUND_RED| BACKGROUND_GREEN );
	cout << "Quitter";

	cli.resetColor();
}

void CLI::getPlayerCoords( unsigned int& x, unsigned int& y, Direction* dir ) {
	Functions::Keys::Key key;
	x = 0;
	y = 0;

	display();
	highlightSelectedPiece( x, y );

	for( bool loop = true; loop; ) {
		key = cli.getKey();

		switch( key ) {
			case Functions::Keys::Key::ArrowUp:
				if( y > 0 )
					y--;
				break;
			case Functions::Keys::Key::ArrowDown:
				if( y < this->m_board.size() - 1 )
					y++;
				break;
			case Functions::Keys::Key::ArrowLeft:
				if( x > 0 )
					x--;
				break;
			case Functions::Keys::Key::ArrowRight:
				if( x < this->m_board.begin()->size() - 1 )
					x++;
				break;
			case Functions::Keys::Key::Enter:
				loop = false;
				break;
			default:
				break;
		}

		display();
		highlightSelectedPiece( x, y );
	}

	if( dir != nullptr ) {
		for( bool loop = true; loop; ) {
			loop = false;
			display();

			if( x < this->m_board.begin()->size() - 1 )
				highlightSelectedPiece( x + 1, y, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( x > 0 )
				highlightSelectedPiece( x - 1, y, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( y < this->m_board.size() - 1 )
				highlightSelectedPiece( x, y + 1, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			if( y > 0 )
				highlightSelectedPiece( x, y - 1, BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );

			key = cli.getKey();

			switch( key ) {
				case Functions::Keys::Key::ArrowLeft:
					*dir = Direction::Left;
					break;

				case Functions::Keys::Key::ArrowRight:
					*dir = Direction::Right;
					break;

				case Functions::Keys::Key::ArrowUp:
					*dir = Direction::Up;
					break;

				case Functions::Keys::Key::ArrowDown:
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
	display();
}

void CLI::removePiece( const Object* ) {
	display();
}

void CLI::movePiece( map<const Object*, pair<unsigned int, unsigned int>>& movements ) {
	display();
}

void CLI::orientPiece( const Object*, Direction oldDir ) {
	display();
}

void CLI::playerTurnBegin( Siam::Player& player ) {
	display();
}

void CLI::playerTurnEnd( Siam::Player& player ) {

}

Players::Action CLI::getPlayerAction( Siam::Player& player ) {
	Functions::Keys::Key key;

	while( true ) {
		key = cli.getKey();

		switch( key ) { //what type of turn would you like to take ?
			case Functions::Keys::Key::N1:
				return Players::Action::Add;
			case Functions::Keys::Key::N2:
				return Players::Action::Remove;
			case Functions::Keys::Key::N3:
				return Players::Action::Move;
			case Functions::Keys::Key::N4:
				return Players::Action::Orient;
			case Functions::Keys::Key::N5:
				return Players::Action::Nothing;
			case Functions::Keys::Key::N0:
				throw exceptions::exit_game();
			default:
				break;
		}
	};
}

void CLI::victory( Siam::Player& player ) {
	cli.clearScreen();
	std::cout << "Bravo " << player.getName() << ", tu as gagne!" << std::endl;
	getchar();
}

void CLI::loadDisplayMatrix() {
	std::string tmp;
	std::ostringstream tmp2;

	tmp = " ";
	for( unsigned int i = 0; i < this->m_board.size() - 1; i++ )
		tmp += "_____";
	tmp += "____       ";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < this->m_board.size(); i++ ) {
		tmp += "| ";
		tmp += ( char ) ( 'A' + i );
		tmp += "  ";
	}
	tmp += "|";
	this->m_displayMatrix.push_back( tmp );

	tmp = "";
	for( unsigned int i = 0; i < this->m_board.size(); i++ ) {
		tmp += "|____";
	}
	tmp += "|";
	this->m_displayMatrix.push_back( tmp );

	tmp = " ";
	for( unsigned int i = 0; i < this->m_board.size() - 1; i++ ) {
		tmp += "_____";
	}
	tmp += "____   ____";
	this->m_displayMatrix.push_back( tmp );

	for( unsigned int j = 0; j < this->m_board.size() * 2; j++ ) {
		tmp2.str( "" );
		for( unsigned int i = 0; i < this->m_board[ j / 2 ].size(); i++ ) {
			tmp2 << "|";

			if( !( j % 2 )) {
				tmp2 << "    ";
			} else {
				tmp2 << "____";
			}
		}
		tmp2 << "| |";
		if( !( j % 2 )) {
			tmp2 << " " << j / 2 + 1 << "  |";
		} else {
			tmp2 << "____|";
		}
		this->m_displayMatrix.push_back( tmp2.str());
	}

}
