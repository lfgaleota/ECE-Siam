#ifndef _ECE_SIAM_UI_MAIN_ALLEGRO_HPP_
	#define _ECE_SIAM_UI_MAIN_ALLEGRO_HPP_

	#include <allegro.h>
	#include "../../../../winhack.h"
	#include <jpgalleg.h>
	#include <loadpng.h>
	#include <vector>
	#include <ios>
	#include <fstream>
	#include <sstream>
	#include <stdlib.h>
	#include "../../../../allegro/popup.hpp"
	#include "../audio/FMOD.hpp"
	#include "../../game.hpp"
	#include "../../player.hpp"

	#ifdef USE_DUI
        #include "../../../../lib/dui/inc/dui.h"
    #endif

	#define DIALOG_PLAYERS_WIDTH 700
	#define DIALOG_PLAYERS_HEIGHT 240
	#define DIALOG_PLAYERS_PADDING_H 50

	namespace Siam {
		namespace UI {
			namespace Main {
				#ifdef USE_DUI
                    int allegroGetPlayers( Dialog::CallbackData cd );
                #endif

				class Allegro {
					private:
						Siam::UI::Audio::FMOD& m_fmod;
						#ifdef USE_DUI
                            Dialog m_playersDialog;
                        #endif
						BITMAP* m_page;
						FONT* m_textFont;
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						bool mouseL = false;
						bool prevMouseL = false;
						bool keyEsc = false;
						bool prevKeyEsc = false;
						int choice;
						std::vector<Siam::Player> m_players;

						void loadSprites();
						void loadFonts();
						void loadBackgrounds();
						#ifdef USE_DUI
                            void loadPlayersDialog();
                        #else
                            std::string askPlayerName();
						#endif

						void display();
						void menu();
						void newGame();
						void joinGame();
						void options();

						void freeBitmaps();
					public:
						Allegro( Siam::UI::Audio::FMOD& fmod );

						#ifdef USE_DUI
                            friend int allegroGetPlayers( Dialog::CallbackData cd );
                        #endif
				};
			}
		}
	}

#endif
