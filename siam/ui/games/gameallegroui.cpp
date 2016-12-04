#include "../../inc/ui/games/gameallegroui.hpp"

using namespace Siam;
using namespace Siam::Objects;
using namespace Siam::Matrixs;
using namespace Siam::UI::Games;

bool actionsMenuCallback( int index, int x, int y, void* customParameter ) {
	switch( index ) {
		case 0:
			((Allegro*)customParameter)->setSelectedAction( Players::Action::Add );
			return true;
		case 1:
			((Allegro*)customParameter)->setSelectedAction( Players::Action::Remove );
			return true;
		case 2:
			((Allegro*)customParameter)->setSelectedAction( Players::Action::Move );
			return true;
		case 3:
			((Allegro*)customParameter)->setSelectedAction( Players::Action::Orient );
			return true;
		case 4:
			((Allegro*)customParameter)->setSelectedAction( Players::Action::Nothing );
			return true;
		case 5:
			((Allegro*)customParameter)->showPause();
			return false;
		default:
			return false;
	}
}

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

Types::Type AllegroObject::getType() const {
	return m_type;
}


Allegro::Allegro( const std::vector<std::vector<Object*>>& board, const std::vector<Player>& players, std::vector<Player>::iterator& currentPlayer, Siam::UI::Audio::FMOD& fmod ) : Game( board, players, currentPlayer, fmod ) {
	this->m_fmod.playMusic( "main1" );

	loadSprites();
	loadBackgrounds();
	loadFonts();
	loadMenus();

	m_page = create_bitmap( SCREEN_W, SCREEN_H );
	display();
}

void Allegro::freeBitmaps() {
	for( auto bmp = this->m_bitmaps.begin(); bmp != this->m_bitmaps.end(); bmp++ ) {
		if( bmp->second != nullptr ) {
			destroy_bitmap( bmp->second );
			bmp->second = nullptr;
		}
	}
}

Allegro::~Allegro() {
	this->m_fmod.stopMusic();
}

void Allegro::loadSprites() {
	std::string path;
	BITMAP* bmp;
	std::vector<std::string> bmpNames = {
			"rhinoceros",
			"elephant",
	        "mountain",
	        "case",
	        "caseInv",
	        "actionAdd",
	        "actionRemove",
	        "actionMove",
	        "actionOrient",
	        "actionNothing",
	        "actionPause",
	        "youWin"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/";
		path += bmpName;
		path += ".png";

		bmp = load_bitmap( path.c_str(), NULL );
		if( bmp ) {
			this->m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/";
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
			"mainBg",
			"gameBg"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/";
		path += bmpName;
		path += ".jpg";

		bmp = load_bitmap( path.c_str(), NULL );
		if( bmp ) {
			this->m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/";
			path += bmpName;
			path += ".jpg";
			throw std::ios_base::failure( path );
		}
	}
}

void Allegro::loadFonts() {
	this->m_textFont = load_font( "fonts/droidsans_14_mono.pcx", NULL, NULL );
	if( !this->m_textFont ) {
		throw std::ios_base::failure( "File not found: fonts/droidsans_14_mono.pcx" );
	}
}

void Allegro::loadMenus() {
	std::vector<Functions::Allegro::MenuItem> items;
	std::vector<std::pair<std::string, std::string>> itemsToGenerate = {
		std::make_pair( "actionAdd", "Ajouter" ),
		std::make_pair( "actionRemove", "Enlever" ),
		std::make_pair( "actionMove", "Deplacer" ),
		std::make_pair( "actionOrient", "Orienter" ),
		std::make_pair( "actionNothing", "Passer son tour" ),
		std::make_pair( "actionPause", "Pause" )
	};

	for( unsigned int i = 0; i < itemsToGenerate.size(); i++ ) {
		items.push_back( Functions::Allegro::MenuItem( this->m_bitmaps.find( itemsToGenerate[ i ].first )->second, itemsToGenerate[ i ].second, makecol( 254 - i * 6, 254 - i * 6, 254 - i * 6 ), makecol( 200, 200, 200 ), makecol( 0, 0, 0 ), actionsMenuCallback ) );
	}

	this->m_actionsMenu = new Functions::Allegro::CircularMenu( SCREEN_W / 2 , SCREEN_H / 2, ( this->m_board.size() - 1 ) * this->m_bitmaps.find( "case" )->second->w + ACTION_MENU_RADIUS_PADDING, ACTION_MENU_SIZE, items, this->m_textFont );
	this->m_actionsMenu->compute();
}

BITMAP* Allegro::getAnimalSprite( Types::Type animal ) const {
	switch( animal ) {
		case Types::Type::Elephant:
			return this->m_bitmaps.find( "elephant" )->second;
		case Types::Type::Rhinoceros:
			return this->m_bitmaps.find( "rhinoceros" )->second;
		case Types::Type::Mountain:
			return this->m_bitmaps.find( "mountain" )->second;
		default:
			throw exceptions::invalid_object_type();
	}
}

void Allegro::displayMatrix() {
	BITMAP* sprite;
	int x, y, pos_x = 0, pos_y = 0;
	bool inv = false;
	BITMAP *caseNormal = this->m_bitmaps.find( "case" )->second;
	BITMAP *caseInv = this->m_bitmaps.find( "caseInv" )->second;

	pos_x = ( SCREEN_W - this->m_board.begin()->size() * caseNormal->w ) / 2;
	pos_y = ( SCREEN_H - this->m_board.size() * caseNormal->h ) / 2;

	for( unsigned int j = 0; j < this->m_board.size(); j++ ) { //browse
		for( unsigned int i = 0; i < this->m_board[ j ].size(); i++ ) {
			if( inv ) {
				draw_sprite( this->m_page, caseInv, pos_x + i * caseInv->w, pos_y + j * caseInv->h );
			} else {
				draw_sprite( this->m_page, caseNormal, pos_x + i * caseNormal->w, pos_y + j * caseNormal->h );
			}
			inv ^= true;
		}
	}

	for( const auto& objpair : this->m_objects ) {
		sprite = getAnimalSprite( objpair.second.getType() );
		x = pos_x + objpair.second.getX() * caseNormal->w + ( caseNormal->w - sprite->w ) / 2;
		y = pos_y + objpair.second.getY() * caseNormal->h + ( caseNormal->h - sprite->h ) / 2;

		switch( objpair.second.getDirection() ) {
			case Direction::Right:
				draw_trans_sprite( this->m_page, sprite, x, y );
				break;
			case Direction::Left:
				rotate_sprite_v_flip_trans( this->m_page, sprite, x, y, itofix( 128 ) );
				break;
			case Direction::Up:
				rotate_sprite_trans( this->m_page, sprite, x, y, itofix( 192 ) );
				break;
			case Direction::Down:
				rotate_sprite_trans( this->m_page, sprite, x, y, itofix( 64 ) );
				break;
		}
	}
}

void Allegro::displayPlayers() {
	int pos_x = 0, pos_y = 0;

	if( this->m_currentPlayer == this->m_players.begin() ) {
		rectfill( this->m_page, 0, 0, SCREEN_W / 2, this->m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_ACTIVE_PLAYER );
		rectfill( this->m_page, SCREEN_W / 2, 0, SCREEN_W, this->m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_INACTIVE_PLAYER );
	} else {
		rectfill( this->m_page, 0, 0, SCREEN_W / 2, this->m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_INACTIVE_PLAYER );
		rectfill( this->m_page, SCREEN_W / 2, 0, SCREEN_W, this->m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_ACTIVE_PLAYER );
	}

	pos_y = ( SCREEN_H - this->m_bitmaps.find( "case" )->second->h * PLAYER_MAX_NUMBER_OF_PIECES ) / 2;

	for( unsigned int i = 0; i < this->m_players.size(); i++ ) {
		textprintf_ex( this->m_page, this->m_textFont, ( !( i % 2 ) ? 0 : SCREEN_W / 2 ) + PLAYER_NAME_PADDING_W, PLAYER_NAME_PADDING_H, makecol( 255, 255, 255 ), -1, "%s", this->m_players[ i ].getName().c_str() );

		if( i == 0 )
			pos_x = 0;
		else
			pos_x = SCREEN_W - this->m_bitmaps.find( "case" )->second->w;

		for( unsigned int j = 0; j < PLAYER_MAX_NUMBER_OF_PIECES; j++ ) {
			if( j < this->m_players[ i ].getRemainingObjects() ) {
				draw_trans_sprite( this->m_page, getAnimalSprite( this->m_players[ i ].getAnimalChosen() ), pos_x, pos_y + j * this->m_bitmaps.find( "case" )->second->h );
			}
		}
	}
}

void Allegro::displayCurrentAction() {
	std::string action = "";
	BITMAP* icon;
	int y = SCREEN_H - ACTION_PANE_PADDING * 2 - this->m_textFont->height;
	if( this->m_selectedAction != Siam::Players::Action::Nothing ) {
		switch( this->m_selectedAction ) {
			case Players::Action::Add:
				action = "Ajouter";
				icon = this->m_bitmaps.find( "actionAdd" )->second;
				break;
			case Players::Action::Remove:
				action = "Enlever";
				icon = this->m_bitmaps.find( "actionRemove" )->second;
				break;
			case Players::Action::Move:
				action = "Deplacer";
				icon = this->m_bitmaps.find( "actionMove" )->second;
				break;
			case Players::Action::Orient:
				action = "Orienter";
				icon = this->m_bitmaps.find( "actionOrient" )->second;
				break;
			default:
				action = "Rien";
				icon = this->m_bitmaps.find( "actionNothing" )->second;
				break;
		}

		rectfill( this->m_page, 0, y, SCREEN_W, SCREEN_H, ACTION_PANE_COLOR );
		textprintf_centre_ex( this->m_page, this->m_textFont, SCREEN_W / 2, y + ACTION_PANE_PADDING, makecol( 0, 0, 0 ), -1, "%s", action.c_str() );
		draw_trans_sprite( this->m_page, icon, ( SCREEN_W - text_length( this->m_textFont, action.c_str() ) ) / 2 - icon->w - ACTION_PANE_PADDING, y + ACTION_PANE_PADDING + ( this->m_textFont->height - icon->h ) / 2 );
	}
}

void Allegro::display( bool update ) {
	stretch_blit( this->m_bitmaps.find( "gameBg" )->second, this->m_page, 0, 0, this->m_bitmaps.find( "gameBg" )->second->w, this->m_bitmaps.find( "gameBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H);

	set_alpha_blender();

	displayMatrix();
	displayPlayers();
	displayCurrentAction();

	set_trans_blender( 255, 0, 255, 0 );

	this->m_actionsMenu->show( this->m_page, mouse_x, mouse_y );

	if( update )
		blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
}

void Allegro::showPause() {
	std::vector<std::string> choices = { "Continuer", "Couper/Remettre les sons", "Quitter" };
	Functions::Allegro::Popup pause = Functions::Allegro::Popup( "Pause", choices, this->m_textFont );
	switch( pause.getChoice() ) {
		case 3:
			throw exceptions::exit_game();
		default:
			break;
	}
}

void Allegro::updateInputs() {
	this->prevMouseL = this->mouseL;
	this->mouseL = (bool) ( mouse_b & 1 );

	this->prevKeyEsc = this->keyEsc;
	this->keyEsc = (bool) key[ KEY_ESC ];

	if( !this->prevKeyEsc && this->keyEsc ) {
		if( this->m_selectedAction == Players::Action::Nothing )
			showPause();
		else {
			this->m_selectedAction = Players::Action::Nothing;
			throw exceptions::cancel_action();
		}
	}
}

void Allegro::highlightSelectedPiece( unsigned int x, unsigned int y, int color ) {
	unsigned int rw, rh, posx, posy;
	if( x < this->m_board.begin()->size() && y < this->m_board.size() ) {
		rw = this->m_bitmaps.find( "case" )->second->w;
		rh = this->m_bitmaps.find( "case" )->second->h;
		posx = ( SCREEN_W - this->m_board.begin()->size() * rw ) / 2;
		posy = ( SCREEN_H - this->m_board.size() * rh ) / 2;

		set_trans_blender( 0, 0, 0, COLOR_SELECTION_BLENDFACTOR );
		drawing_mode( DRAW_MODE_TRANS, NULL, 0, 0 );
		rectfill( this->m_page, posx + x * rw, posy + y * rh, posx + x * rw + rw, posy + y * rh + rh, color );
		drawing_mode( DRAW_MODE_SOLID, NULL, 0, 0 );

		set_alpha_blender();
	}
}

void Allegro::getPlayerCoords( unsigned int& x, unsigned int& y, Matrixs::Direction* dir ) {
	int mx, my;
	unsigned int rw, rh, posx, posy;
	x = 0;
	y = 0;

	rw = this->m_bitmaps.find( "case" )->second->w;
	rh = this->m_bitmaps.find( "case" )->second->h;
	posx = ( SCREEN_W - this->m_board.begin()->size() * rw ) / 2;
	posy = ( SCREEN_H - this->m_board.size() * rh ) / 2;

	display( false );
	highlightSelectedPiece( x, y );
	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

	this->prevMouseL = true;

	for( bool loop = true; loop; ) {
		updateInputs();

		display( false );
		highlightSelectedPiece( x, y );
		blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

		mx = ( mouse_x - posx ) / rw;
		my = ( mouse_y - posy ) / rh;

		if( mx >= 0 && my >= 0 && (unsigned) mx < this->m_board.begin()->size() && (unsigned) my < this->m_board.size() ) {
			x = (unsigned) mx;
			y = (unsigned) my;

			if( !this->prevMouseL && this->mouseL ) {
				loop = false;
				this->prevMouseL = true;
			}
		}
	}

	if( dir != nullptr ) {
		for( bool loop = true; loop; ) {
			updateInputs();

			display( false );
			if( x < this->m_board.begin()->size() - 1 )
				highlightSelectedPiece( x + 1, y, COLOR_DIRECTION_SELECTION );
			if( x > 0 )
				highlightSelectedPiece( x - 1, y, COLOR_DIRECTION_SELECTION );
			if( y < this->m_board.size() - 1 )
				highlightSelectedPiece( x, y + 1, COLOR_DIRECTION_SELECTION );
			if( y > 0 )
				highlightSelectedPiece( x, y - 1, COLOR_DIRECTION_SELECTION );

			mx = ( mouse_x - posx ) / rw;
			my = ( mouse_y - posy ) / rh;

			highlightSelectedPiece( (unsigned) mx, (unsigned) my );
			blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

			if( mx >= 0 && my >= 0 && (unsigned) mx < this->m_board.begin()->size() && (unsigned) my < this->m_board.size() ) {
				if( (unsigned) mx == x + 1 && (unsigned) my == y ) {
					*dir = Direction::Right;
				} else if( (unsigned) mx == x - 1 && (unsigned) my == y ) {
					*dir = Direction::Left;
				} else if( (unsigned) mx == x && (unsigned) my == y + 1 ) {
					*dir = Direction::Down;
				} else if( (unsigned) mx == x && (unsigned) my == y - 1 ) {
					*dir = Direction::Up;
				}

				if( !this->prevMouseL && this->mouseL ) {
					loop = false;
					this->prevMouseL = true;
				}
			}
		}
	}
}

void Allegro::addPiece( const Object* object, unsigned int x, unsigned int y ) {
	if( object != nullptr )
		this->m_objects.insert( std::make_pair( object, AllegroObject( x, y, object->getType(), object->getDirection() ) ) );

	display();
}

void Allegro::removePiece( const Object* object ) {
	this->m_objects.erase( object );

	display();
}

void Allegro::movePiece( std::map<const Object*, std::pair<unsigned int, unsigned int>>& movements ) {
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

void Allegro::ejectPiece( const Object* object ) {
	this->m_objects.erase( object );

	display();
}

void Allegro::playerTurnBegin( Player& player ) {
	this->m_selectedAction = Players::Action::Nothing;

	display();
}

void Allegro::playerTurnEnd( Player& player ) {
	display();
}

Players::Action Allegro::getPlayerAction( Player& player ) {
	this->m_actionsMenu->open();

	for( bool loop = true; loop; ) {
		updateInputs();

		if( !this->prevMouseL && this->mouseL ) {
			if( this->m_actionsMenu->handleClick( mouse_x, mouse_y, this ) ) {
				loop = false;
			}
		}

		display();
	}

	this->m_actionsMenu->close();

	return this->m_selectedAction;
}

void Allegro::victory( Player& player ) {
	stretch_blit( this->m_bitmaps.find( "mainBg" )->second, this->m_page, 0, 0, this->m_bitmaps.find( "mainBg" )->second->w, this->m_bitmaps.find( "mainBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H);

	set_alpha_blender();
	draw_trans_sprite( this->m_page, this->m_bitmaps.find( "youWin" )->second, ( SCREEN_W - this->m_bitmaps.find( "youWin" )->second->w ) / 2, VICTORY_PADDING );

	textprintf_centre_ex( this->m_page, this->m_textFont, SCREEN_W / 2, SCREEN_H / 2, makecol( 255, 255, 255 ), -1, "Bravo %s! Tu as gagne!", player.getName().c_str() );

	blit( this->m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

	this->m_fmod.stopMusic();
	this->m_fmod.playSoundWait( "victory" );
	this->m_fmod.playMusic( "victory" );

	textprintf_centre_ex( screen, this->m_textFont, SCREEN_W / 2, SCREEN_H - this->m_textFont->height - VICTORY_PADDING, makecol( 255, 255, 255 ), -1, "Continuer >" );

	this->prevMouseL = true;

	for( bool loop = true; loop; ) {
		updateInputs();
		if( !this->prevMouseL && this->mouseL )
			loop = false;
	}

	freeBitmaps();
}

void Allegro::showError( std::string msg ) {
	Functions::Allegro::Popup popup( msg );
}

void Allegro::setSelectedAction( Siam::Players::Action action ) {
	this->m_selectedAction = action;
}
