#include "../../inc/ui/main/mainallegroui.hpp"

using namespace Siam;
using namespace Siam::UI::Main;
using namespace Siam::UI::Audio;

Allegro::Allegro( Siam::UI::Audio::FMOD& fmod ) : m_fmod( fmod ) {
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
		throw std::runtime_error( "Allegro initialization failed" );
	}

	set_window_title( "ECE-Siam" );

	enable_hardware_cursor();
	select_mouse_cursor( 2 );
	show_mouse( screen );

	this->m_fmod.playMusic( "menu" );

	loadSprites();
	loadBackgrounds();
	loadFonts();
	loadPlayersDialog();

	m_page = create_bitmap( SCREEN_W, SCREEN_H );
	display();

	menu();

	freeBitmaps();
	allegro_exit();
	exit( 0 );
}

void Allegro::loadSprites() {
	std::string path;
	BITMAP* bmp;
	std::vector<std::string> bmpNames = {
		"logo",
	    "menu0",
		"menu1",
		"menu2",
		"menu3",
		"menu4",
	    "menuCol"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/menu/";
		path += bmpName;
		path += ".png";

		bmp = load_bitmap( path.c_str(), NULL );
		if( bmp ) {
			this->m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/menu/";
			path += bmpName;
			path += ".png";
			throw std::ios_base::failure( path );
		}
	}
}

void Allegro::loadBackgrounds() {
	std::string path;
	BITMAP* bmp;
	std::vector<std::string> bmpNames = {
		"mainBg"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/menu/";
		path += bmpName;
		path += ".jpg";

		bmp = load_bitmap( path.c_str(), NULL );
		if( bmp ) {
			this->m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/menu/";
			path += bmpName;
			path += ".png";
			throw std::ios_base::failure( path );
		}
	}
}

void Allegro::loadFonts() {
	this->m_textFont = load_font( "fonts/droidsans_14_mono.pcx", NULL, NULL );
	if( !this->m_textFont ) {
		throw std::ios_base::failure( "File not found: fonts/droidsans_14_mono.pcx" );
	}
	font = this->m_textFont;
}

void Allegro::freeBitmaps() {
	for( auto bmp = this->m_bitmaps.begin(); bmp != this->m_bitmaps.end(); bmp++ ) {
		if( bmp->second != nullptr ) {
			destroy_bitmap( bmp->second );
			bmp->second = nullptr;
		}
	}
}

void Allegro::display() {
	stretch_blit( this->m_bitmaps.find( "mainBg" )->second, this->m_page, 0, 0, this->m_bitmaps.find( "mainBg" )->second->w, this->m_bitmaps.find( "mainBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H);

	set_alpha_blender();

	// Récupération de la couleur
	int item = getr( getpixel( this->m_bitmaps.find( "menuCol" )->second, mouse_x, mouse_y ) ) / 40;

	// Tests successifs des couleurs puis affichage à l'ecran d'un nouveau avant-plan et sélection du choix
	if( item == 1 ) {
		draw_trans_sprite( this->m_page, this->m_bitmaps.find( "menu1" )->second, 0, 0 );
		this->choice = item;
	} else if( item == 2 ) {
		draw_trans_sprite( this->m_page, this->m_bitmaps.find( "menu2" )->second, 0, 0 );
		this->choice = item;
	} else if( item == 3 ) {
		draw_trans_sprite( this->m_page, this->m_bitmaps.find( "menu3" )->second, 0, 0 );
		this->choice = item;
	} else if( item == 4 ) {
		draw_trans_sprite( this->m_page, this->m_bitmaps.find( "menu4" )->second, 0, 0 );
		this->choice = item;
	} else {
		draw_trans_sprite( this->m_page, this->m_bitmaps.find( "menu0" )->second, 0, 0 );
		this->choice = 0;
	}

	draw_trans_sprite( this->m_page, this->m_bitmaps.find( "logo" )->second, SCREEN_W - 50 - this->m_bitmaps.find( "logo" )->second->w, 100 );

	blit( this->m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
}

void Allegro::menu() {
	for( bool loop = true; loop; ) {
		this->prevMouseL = this->mouseL;
		this->mouseL = (bool) ( mouse_b & 1 );

		if( !this->prevMouseL && this->mouseL ) {
			switch( this->choice ) {
				case 1:
					// Nouvelle partie
					newGame();
					break;
				case 3:
					// Options
					options();
					break;
				case 4:
					//Quitter
					loop = false;
					break;
				default:
					break;
			}
		}

		display();
	}
}

void Allegro::options() {

}

void Allegro::loadPlayersDialog() {
	std::ostringstream thisptr;
	thisptr << (size_t) this;
	std::ifstream playersDialogFile( "ui/selectPlayers.dui" );
	if( !playersDialogFile.is_open() ) {
		throw std::ios_base::failure( "File not found: ui/selectPlayers.dui" );
	}
	std::stringstream playerDialogStream;
	playerDialogStream << playersDialogFile.rdbuf();
	std::string playersDialogString = playerDialogStream.str();
	size_t start_pos = playersDialogString.find( "allegptr" );
    if( start_pos != std::string::npos )
		playersDialogString.replace( start_pos, 8, thisptr.str() );
	std::stringstream playerDialogStreamModified;
	playerDialogStreamModified << playersDialogString;

	this->m_playersDialog = Dialog( playerDialogStreamModified );
	this->m_playersDialog.setCallback( "getPlayers", allegroGetPlayers );
}

void Allegro::newGame() {
	this->m_players.clear();

	stretch_blit( this->m_bitmaps.find( "mainBg" )->second, screen, 0, 0, this->m_bitmaps.find( "mainBg" )->second->w, this->m_bitmaps.find( "mainBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H );
	rectfill( screen, ( SCREEN_W - DIALOG_PLAYERS_WIDTH ) / 2, ( SCREEN_H - DIALOG_PLAYERS_HEIGHT ) / 2 - DIALOG_PLAYERS_PADDING_H, ( SCREEN_W + DIALOG_PLAYERS_WIDTH ) / 2, ( SCREEN_H + DIALOG_PLAYERS_HEIGHT ) / 2 + DIALOG_PLAYERS_PADDING_H, makecol( 200, 200, 200 ) );

	centre_dialog( &this->m_playersDialog.dialog[ 0 ] );

	this->m_playersDialog.doDialog();

	if( this->m_players.size() > 0 ) {
		this->m_fmod.stopMusic();

		Siam::Game game( this->m_players, this->m_fmod, true );

		this->m_fmod.playMusic( "menu" );
	}
}

int Siam::UI::Main::allegroGetPlayers( Dialog::CallbackData cd ) {
	std::istringstream allegptr;
	size_t allegint;
	Allegro* alleg = nullptr;
	std::string player1name, player2name;

	player1name = Dialog::registry( 0 );
	player2name = Dialog::registry( 1 );

	/*Dialog *d = Dialog::getActiveDialog();
	bool player1local = Xml::find( d->xmlCache, "id", "player1local" )[ 0 ]->attr[ "flags" ].str != "0";
	bool player1ai = Xml::find( d->xmlCache, "id", "player1ai" )[ 0 ]->attr[ "flags" ].str != "0";
	bool player2local = Xml::find( d->xmlCache, "id", "player2local" )[ 0 ]->attr[ "flags" ].str != "0";
	bool player2ai = Xml::find( d->xmlCache, "id", "player2ai" )[ 0 ]->attr[ "flags" ].str != "0";*/

	allegptr.str( cd.parameters[ 0 ] );
	allegptr >> allegint;
	alleg = (Allegro*) allegint;

	if( player1name != "" && player2name != "" ) {
		alleg->m_players.push_back( Player( player1name, Objects::Types::Type::Rhinoceros ) );
		alleg->m_players.push_back( Player( player2name, Objects::Types::Type::Elephant ) );
	}

	return D_EXIT;
}