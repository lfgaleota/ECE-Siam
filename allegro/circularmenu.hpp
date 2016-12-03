#ifndef _FUNCTIONS_ALLEGRO_CIRCULARMENU_HPP_
	#define _FUNCTIONS_ALLEGRO_CIRCULARMENU_HPP_

	#include <vector>
	#include <string>
	#include <ios>
	#include <allegro.h>
	#include "../winhack.h"
	#include <loadpng.h>
	#include <jpgalleg.h>
	#include <cmath>

	#ifndef M_PI
		#define M_PI 3.1415f
	#endif

	namespace Functions {
		namespace Allegro {
			struct MenuItem {
				BITMAP* icon;
				std::string tooltip;
				int bgColor;
				int bgSelColor;
				int textColor;

				bool( *callback )( int index, int mouse_x, int mouse_y, void* customParameter );

				int centerX;
				int centerY;
				int iconX;
				int iconY;

				MenuItem( BITMAP* icon, std::string tooltip, int bgColor, int bgSelColor, int textColor, bool( *callback )( int index, int mouse_x, int mouse_y, void* customParameter ) ) : icon( icon ), tooltip( tooltip ), bgColor( bgColor ), bgSelColor( bgSelColor ), textColor( textColor ), callback( callback ) {}
			};

			class CircularMenu {
				private:
					bool opened;
					int inner_radius;
					int medium_radius;
					int outer_radius;
					float angle;
					int screen_x;
					int screen_y;
					BITMAP* bmp;
					std::vector<MenuItem> items;
					FONT* font;

				public:
					CircularMenu( int x, int y, int radius, int size, std::vector<MenuItem> items, FONT* font );
					~CircularMenu();

					void compute();
					void recompute();

					void updatePosition( int x, int y );

					void show( BITMAP* dest, int x, int y );

					bool handleClick( int x, int y, void* customParameter );

					void open();
					void close();
			};

			#include "invalid_configuration"
		}
	}
#endif