#ifndef _ECE_SIAM_MAINCLIUI_HPP_
	#define _ECE_SIAM_MAINCLIUI_HPP_

	#include <iostream>
	#include <vector>
	#include <ios>
	#include <fstream>
	#include <sstream>
	#include "../../../../cli/cli.hpp"
	#include "../../../../cli/menu/menu.hpp"
	#include "../audio/FMOD.hpp"
	#include "../../game.hpp"
	#include "../../player.hpp"

	#define LOGO_WIDTH 74
	#define LOGO_HEIGHT 18

	namespace Siam {
		namespace UI {
			namespace Main {
				class CLI {
					private:
						Siam::UI::Audio::FMOD& m_fmod;
						std::vector<Siam::Player> m_players;
						Functions::CLI m_cli;
						std::string m_logo;

						void menu();
						void askForPlayers();
					public:
						CLI( Siam::UI::Audio::FMOD& fmod );

						static void logo();
				};
			}
		}
	}
#endif
