#include "popup.hpp"
#include <iostream>
using namespace std;
using namespace Functions::Allegro;

void Popup::generateBackground() {
	string tmp;
	int i, j;

	bg = create_bitmap( width, height );
	if( !bg ) {
		allegro_message( "Erreur d'allocation" );
		throw bitmap_not_loaded( "Popup background image" );
	}

	clear_to_color( bg, makecol( 255, 0, 255 ) );

	BITMAP* bg_texture = load_png( "images/popup/bg.png", NULL );
	if( !bg_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/bg.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* top_texture = load_png( "images/popup/top.png", NULL );
	if( !top_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/top.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* left_texture = load_png( "images/popup/left.png", NULL );
	if( !left_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/left.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* top_left_texture = load_png( "images/popup/top_left.png", NULL );
	if( !top_left_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/top_left.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* top_right_texture = load_png( "images/popup/top_right.png", NULL );
	if( !top_right_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/top_right.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* bottom_left_texture = load_png( "images/popup/bottom_left.png", NULL );
	if( !bottom_left_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/bottom_left.png";
		throw ios_base::failure( tmp );
	}

	BITMAP* bottom_right_texture = load_png( "images/popup/bottom_right.png", NULL );
	if( !bottom_right_texture ) {
		tmp = "File not found: ";
		tmp += "images/popup/bottom_right.png";
		throw ios_base::failure( tmp );
	}

	for( i = MENU_BACK_OFFSET; i < height - MENU_BACK_OFFSET; i += bg_texture->h ) {
		for( j = MENU_BACK_OFFSET; j < width - MENU_BACK_OFFSET; j += bg_texture->w ) {
			masked_blit( bg_texture, bg, 0, 0, j, i, bg_texture->w, bg_texture->h );
		}
	}

	for( j = MENU_BACK_OFFSET; j < width - MENU_BACK_OFFSET; j += top_texture->w ) {
		masked_blit( top_texture, bg, 0, 0, j, MENU_LEFT_BAR_OFFSET, top_texture->w, top_texture->h );
		masked_blit( top_texture, bg, 0, 0, j, height - MENU_LEFT_BAR_OFFSET - top_texture->h, top_texture->w, top_texture->h );
	}

	for( i = MENU_BACK_OFFSET; i < height - MENU_BACK_OFFSET; i += left_texture->h ) {
		masked_blit( left_texture, bg, 0, 0, MENU_TOP_BAR_OFFSET, i, left_texture->w, left_texture->h );
		masked_blit( left_texture, bg, 0, 0, width - MENU_TOP_BAR_OFFSET - left_texture->w, i, left_texture->w, left_texture->h );
	}

	rectfill( bg, 0, 0, MENU_TOP_BAR_OFFSET, bg->h, makecol( 255, 0, 255 ) );
	rectfill( bg, 0, 0, bg->w, MENU_LEFT_BAR_OFFSET, makecol( 255, 0, 255 ) );
	rectfill( bg, 0, bg->h - MENU_TOP_BAR_OFFSET, bg->w, bg->h, makecol( 255, 0, 255 ) );
	rectfill( bg, bg->w - MENU_LEFT_BAR_OFFSET, 0, bg->w, bg->h, makecol( 255, 0, 255 ) );

	masked_blit( top_left_texture, bg, 0, 0, 0, 0, top_left_texture->w, top_left_texture->h );
	masked_blit( top_right_texture, bg, 0, 0, width - top_right_texture->w, 0, top_right_texture->w, top_right_texture->h );
	masked_blit( bottom_left_texture, bg, 0, 0, 0, height - bottom_left_texture->h, bottom_left_texture->w, bottom_left_texture->h );
	masked_blit( bottom_right_texture, bg, 0, 0, width - bottom_right_texture->w, height - bottom_right_texture->h, bottom_right_texture->w, bottom_right_texture->h );

	destroy_bitmap( bg_texture );
	destroy_bitmap( top_texture );
	destroy_bitmap( left_texture );
	destroy_bitmap( top_left_texture );
	destroy_bitmap( top_right_texture );
	destroy_bitmap( bottom_left_texture );
	destroy_bitmap( bottom_right_texture );
}

Popup::Popup( std::string title, std::vector<std::string> choices, FONT* fonttext ) {
	BITMAP *page, *save;
	int quit = 0, start_x, start_y, end_x, selected_button;
	bool prev_mouse_l, mouse_l = 1, prev_key_down, key_down = 1, prev_key_up, key_up = 1, prev_key_enter, key_enter = 1, prev_key_esc, key_esc = 1;
	size_t size, max_size, count = choices.size();
	char font_loaded = 0;

	if( fonttext == NULL ) {
		fonttext = load_font( "polices/droidsans_14_mono.pcx", NULL, NULL );
		font_loaded = 1;

		if( fonttext == NULL ) {
			font_loaded = 0;
			allegro_message( "Imoossible de charger la police pour le menu." );
			fonttext = font;
		}
	}

	this->height = MENU_PADDING_Y * 2 + ( count + 1 ) * MENU_LETTER_SPACING_Y + ( count + 2 ) * MENU_FONT_SIZE_Y;
	this->width = MENU_PADDING_X * 2;
	max_size = title.size();

	for( const auto& choicetxt : choices ) {
		size = choicetxt.size();
		if( size > max_size )
			max_size = size;
	}

	width += max_size * MENU_FONT_SIZE_X * MENU_LETTER_SPACING_X;

	generateBackground();
	if( !this->bg ) {
		return;
	}

	page = create_bitmap( SCREEN_W, SCREEN_H );
	if( !page ) {
		allegro_message( "Erreur d'allocation" );
		return;
	}

	save = create_bitmap( SCREEN_W, SCREEN_H );
	if( save )
		blit( screen, save, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

	start_y = ( SCREEN_H - height ) / 2 +  2 * MENU_PADDING_Y + MENU_FONT_SIZE_Y;
	start_x = ( SCREEN_W - width ) / 2 + MENU_PADDING_X;
	end_x = ( SCREEN_W + width ) / 2 - MENU_PADDING_X;

	while( !quit ) {
		prev_mouse_l = mouse_l;
		mouse_l = (bool) ( mouse_b & 1 );

		prev_key_down = key_down;
		key_down = key[ KEY_DOWN ];

		prev_key_up= key_up;
		key_up = key[ KEY_UP ];

		prev_key_enter = key_enter;
		key_enter = key[ KEY_ENTER ];

		prev_key_esc = key_esc;
		key_esc = key[ KEY_ESC ];

		if( !prev_key_enter && key_enter )
			quit = 1;

		if( !prev_key_up && key_up ) {
			if( this->choice > 1 )
				this->choice--;
		}

		if( !prev_key_down && key_down ) {
			if( this->choice < count )
				this->choice++;
		}

		if( !prev_key_esc && key_esc ) {
			this->choice = 0;
			quit = 1;
		}

		if( save )
			blit( save, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

		masked_blit( bg, page, 0, 0, ( SCREEN_W - width ) / 2, ( SCREEN_H - height ) / 2, SCREEN_W, SCREEN_H );

		if( mouse_x >= start_x && mouse_x <= end_x ) {
			selected_button = ( mouse_y - start_y ) / ( MENU_FONT_SIZE_Y + MENU_LETTER_SPACING_Y );
			if( selected_button >= 0 && (unsigned) selected_button < count ) {
				this->choice = (unsigned) selected_button + 1;
			}

			if( !prev_mouse_l && mouse_l ) {
				quit = 1;
			}
		}

		textprintf_centre_ex( page, fonttext, SCREEN_W / 2, ( SCREEN_H - height ) / 2 + MENU_PADDING_Y, makecol( 255, 255, 255 ), -1, title.c_str() );

		for( unsigned i = 0; i < count; i++ ) {
			if( i == this->choice - 1 )
				textprintf_centre_ex( page, fonttext, SCREEN_W / 2, ( SCREEN_H - height ) / 2 + MENU_PADDING_Y + ( i + 2 ) * ( MENU_FONT_SIZE_Y + MENU_LETTER_SPACING_Y ), makecol( 255, 255, 255 ), -1, choices[ i ].c_str() );
			else
				textprintf_centre_ex( page, fonttext, SCREEN_W / 2, ( SCREEN_H - height ) / 2 + MENU_PADDING_Y + ( i + 2 ) * ( MENU_FONT_SIZE_Y + MENU_LETTER_SPACING_Y ), makecol( 255, 255, 0 ), -1, choices[ i ].c_str() );
		}

		blit( page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	}

	destroy_bitmap( bg );
	if( save )
		destroy_bitmap( save );
	destroy_bitmap( page );

	if( font_loaded )
		destroy_font( fonttext );
}

Popup::Popup( std::string title, std::string button, FONT* fonttext ) {
	bool font_loaded = 0;

	if( fonttext == NULL ) {
		fonttext = load_font( "fonts/droidsans_14_mono.pcx", NULL, NULL );
		font_loaded = 1;

		if( fonttext == NULL ) {
			font_loaded = 0;
			allegro_message( "Impossible de charger la police pour le menu." );
			fonttext = font;
		}
	}

	if( button == "" ) {
		vector<string> choices = { "OK" };

		Popup( title, choices, fonttext );
	} else {
		vector<string> choices = { button };

		Popup( title, choices, fonttext );
	}

	if( font_loaded ) {
		destroy_font( fonttext );
	}
}

int Popup::getChoice() const {
	return this->choice;
}
