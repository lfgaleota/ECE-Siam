#include "../../inc/ui/games/gameallegroui.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;
using namespace Siam::UI::Games;

AllegroObject::AllegroObject() : m_x( 0 ), m_y( 0 ), m_type( Types::Type::Object ), m_direction( Direction::Left ) {}

AllegroObject::AllegroObject( unsigned int x, unsigned int y, Types::Type type, Direction direction ) : m_x( x ), m_y( y ), m_type( type ), m_direction( direction ) {}

unsigned int AllegroObject::getX() const {
	return this->m_x;
}

void AllegroObject::setX( unsigned int x ) {
	this->m_x = x;
}

unsigned int AllegroObject::getY() const {
	return this->m_y;
}

void AllegroObject::setY( unsigned int y ) {
	this->m_y = y;
}

Direction AllegroObject::getDirection() const {
	return m_direction;
}

void AllegroObject::setDirection( Direction direction ) {
	this->m_direction = direction;
}

Allegro::Allegro( const vector<vector<Object*>>& board, const vector<Player>& players, vector<Player>::iterator& currentPlayer ) : Game( board, players, currentPlayer ) {
	allegro_init();
	install_mouse();
	install_keyboard();

	jpgalleg_init();
	register_png_file_type();
	install_keyboard();
	install_mouse();

	set_color_depth( desktop_color_depth() );
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0 ) != 0 ) {
		allegro_message( "probleme mode graphique" );
		allegro_exit();
		throw runtime_error( "Allegro initialization failed" );
	}

	set_window_title( "ECE-Siam" );

	enable_hardware_cursor();
	select_mouse_cursor( 2 );
	show_mouse( screen );

	loadSprites();
	page = create_bitmap( SCREEN_W, SCREEN_H );
	display();
}

Allegro::~Allegro() {
	for( auto& bmp : this->m_bitmaps ) {
		destroy_bitmap( bmp.second );
	}
}

void Allegro::loadSprites() {
	string path;
	BITMAP* bmp;
	vector<string> bmpNames = {
			"rhinoceros",
			"elephant",
	        "mountain",
	        "case"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/";
		path += bmpName;
		path += ".png";

		bmp = load_bitmap( path.c_str(), 0 );
		if( bmp != nullptr ) {
			this->m_bitmaps.insert( make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/";
			path += bmpName;
			path += ".png";
			throw ios_base::failure( path );
		}
	}
}

void Allegro::showError( string msg ) {
	Functions::Allegro::Popup( "Erreur", msg );
}

void Allegro::display() {
	clear_bitmap( page );

	blit( page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
}


void Allegro::getPlayerCoords( unsigned int& x, unsigned int& y, Matrixs::Direction* dir ) {

}

void Allegro::addPiece( const Object* object, unsigned int x, unsigned int y ) {
	if( object != nullptr )
		this->m_objects.insert( make_pair( object, AllegroObject( x, y, object->getType(), object->getDirection() ) ) );

	display();
}

void Allegro::removePiece( const Object* object ) {
	this->m_objects.erase( object );

	display();
}

void Allegro::movePiece( map<const Object*, pair<unsigned int, unsigned int>>& movements ) {
	for( const auto& movement : movements ) {
		if( movement.first != nullptr ) {
			this->m_objects[ movement.first ].setX( movement.second.first );
			this->m_objects[ movement.first ].setY( movement.second.second );
		}
	}

	display();
}

void Allegro::orientPiece( const Object* object ) {
	if( object != nullptr )
		this->m_objects[ object ].setDirection( object->getDirection() );

	display();
}

void Allegro::playerTurnBegin( Player& player ) {
	display();
}

void Allegro::playerTurnEnd( Player& player ) {
	display();
}

Players::Action Allegro::getPlayerAction( Player& player ) {
	return Players::Action::Nothing;
}

void Allegro::victory( Player& player ) {

}