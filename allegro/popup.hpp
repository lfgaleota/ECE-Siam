#ifndef _ALLEGRO_POPUP_HPP_
	#define _ALLEGRO_POPUP_HPP_

	#include <vector>
	#include <string>
	#include <ios>
	#include <allegro.h>
	#include "../winhack.h"
	#include <allegro.h>
	#include <loadpng.h>

	#define MENU_BACK_OFFSET 4
	#define MENU_TOP_BAR_OFFSET 1
	#define MENU_LEFT_BAR_OFFSET 1
	#define MENU_FONT_SIZE_X 7
	#define MENU_FONT_SIZE_Y 14
	#define MENU_LETTER_SPACING_X 2
	#define MENU_LETTER_SPACING_Y 5
	#define MENU_PADDING_Y 20
	#define MENU_PADDING_X 25

	namespace Functions {
		namespace Allegro {
			class Popup {
				private:
					unsigned int width = 0;
					unsigned int height = 0;
					BITMAP* bg = nullptr;
					unsigned int choice = 0;

					void generateBackground();

				public:
					Popup( std::string title, std::vector<std::string> choices, FONT* fonttext );
					Popup( std::string title, std::string button = "", FONT* fonttext = NULL );

					int getChoice() const;
			};

			#include "bitmap_not_loaded"
		}
	}


#endif
