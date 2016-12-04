#include "circularmenu.hpp"

using namespace std;
using namespace Functions::Allegro;

CircularMenu::CircularMenu( int x, int y, int radius, int size, vector<MenuItem> items, FONT* font ) {
	if( radius <= 0 || size <= 0 || items.size() == 0 || !font ) {
		throw invalid_configuration( "Configuration du menu circulaire invalide." );
	}
	this->font = font;
	this->items = items;
	this->inner_radius = radius;
	this->medium_radius = radius + size / 2;
	this->outer_radius = radius + size;
	this->screen_x = x - this->outer_radius;
	this->screen_y = y - this->outer_radius;
	this->opened = false;
}

CircularMenu::~CircularMenu() {
	destroy_bitmap( this->bmp );
}

void CircularMenu::compute() {
	float mid_angle;
	MenuItem *item;
	
	this->bmp = create_bitmap( 2 * this->outer_radius, 2 * this->outer_radius );
	if( !this->bmp ) {
		allegro_message( "Allocation de la bitmap du menu échouée." );
		return;
	}

	this->angle = 2 * M_PI / this->items.size();

	rectfill( this->bmp, 0, 0, this->bmp->w, this->bmp->h, makecol( 255, 0, 255 ) );
	circlefill( this->bmp, this->outer_radius, this->outer_radius, this->outer_radius, 0 );
	circlefill( this->bmp, this->outer_radius, this->outer_radius, this->inner_radius,
	            makecol( 255, 0, 255 ) );

	for( unsigned i = 0; i < this->items.size(); i++ ) {
		item = &this->items[ i ];

		mid_angle = ( this->angle * ( i + 1 ) + this->angle * i ) / 2;
		item->centerX = this->outer_radius + this->medium_radius * cosf( mid_angle );
		item->centerY = this->outer_radius + this->medium_radius * sinf( mid_angle );

		line( this->bmp, this->outer_radius, this->outer_radius,
		      this->outer_radius + this->outer_radius * cosf( this->angle * i ),
		      this->outer_radius + this->outer_radius * sinf( this->angle * i ), makecol( 255, 0, 255 ) );
		line( this->bmp, this->outer_radius, this->outer_radius,
		      this->outer_radius + this->outer_radius * cosf( this->angle * ( i + 1 ) ),
		      this->outer_radius + this->outer_radius * sinf( this->angle * ( i + 1 ) ), makecol( 255, 0, 255 ) );
		floodfill( this->bmp, item->centerX, item->centerY, item->bgColor );

		item->iconX = this->screen_x + item->centerX - item->icon->w / 2;
		item->iconY = this->screen_y + item->centerY - item->icon->w / 2;
	}
}

void CircularMenu::recompute() {
	if( this->bmp ) {
		destroy_bitmap( this->bmp );
		this->bmp = NULL;
	}

	compute();
}

void CircularMenu::updatePosition( int x, int y ) {
	this->screen_x = x - this->outer_radius;
	this->screen_y = y - this->outer_radius;

	for( unsigned i = 0; i < this->items.size(); i++ ) {
		this->items[ i ].iconX = this->screen_x + this->items[ i ].centerX - this->items[ i ].icon->w / 2;
		this->items[ i ].iconY = this->screen_y + this->items[ i ].centerY - this->items[ i ].icon->w / 2;
	}
}

void CircularMenu::show( BITMAP* dest, int x, int y ) {
	int col = 0, tooltip_i = -1;

	if( this->opened ) {
		if( ( x >= this->screen_x ) && ( y >= this->screen_y ) && ( x <= ( this->screen_x + this->bmp->w ) ) &&
		    ( y <= ( this->screen_y + this->bmp->h ) ) ) {
			col = getpixel( this->bmp, x - this->screen_x, y - this->screen_y );
		}

		set_trans_blender( 255, 0, 255, 0 );
		masked_blit( this->bmp, dest, 0, 0, this->screen_x, this->screen_y, this->bmp->w, this->bmp->h );

		for( unsigned i = 0; i < this->items.size(); i++ ) {
			if( col > 0 && col == this->items[ i ].bgColor ) {
				floodfill( dest, x, y, this->items[ i ].bgSelColor );
				tooltip_i = i;
			}

			set_alpha_blender();
			draw_trans_sprite( dest, this->items[ i ].icon, this->items[ i ].iconX, this->items[ i ].iconY );
		}

		if( tooltip_i > -1 )
			textprintf_ex( dest, this->font, x + this->font->height, y, this->items[ tooltip_i ].textColor, this->items[ tooltip_i ].bgSelColor, "%s", this->items[ tooltip_i ].tooltip.c_str() );
	}
}

bool CircularMenu::handleClick( int x, int y, void* customParameter ) {
	int col;
	bool ret = false;

	col = getpixel( this->bmp, x - this->screen_x, y - this->screen_y );

	if( this->opened ) {
		for( unsigned int i = 0; i < this->items.size(); i++ ) {
			if( col > 0 && col == this->items[ i ].bgColor ) {
				if( this->items[ i ].callback != nullptr )
					ret = this->items[ i ].callback( i, mouse_x, mouse_y, customParameter );
			}
		}
	}

	return ret;
}

void CircularMenu::open() {
	this->opened = true;
}

void CircularMenu::close() {
	this->opened = false;
}