#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/main/maincliui.hpp"
#include "siam/inc/ui/main/mainallegroui.hpp"

int main( int argc, char* argv[] ) {
	Siam::UI::Audio::FMOD fmod;

	fmod.loadMusic( "menu", "musics/menu.it" );
	fmod.loadMusic( "main1", "musics/main1.it" );
	fmod.loadMusic( "victory", "musics/victorybg.it" );
	fmod.loadSound( "victory", "musics/victory.it" );

	if( argc > 0 ) {
		std::string arg0 = argv[ 0 ];

		if( arg0 == "--cli" ) {
			Siam::UI::Main::CLI ui( fmod );
			return 0;
		}
	}

	Siam::UI::Main::Allegro ui( fmod );
	return 0;
}

END_OF_MAIN()
