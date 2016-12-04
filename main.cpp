#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/main/maincliui.hpp"
#include "siam/inc/ui/main/mainallegroui.hpp"


int main() {
	Siam::UI::Audio::FMOD fmod;


	fmod.loadMusic( "menu", "musics/menu.it" );
	fmod.loadMusic( "main1", "musics/main1.it" );
	fmod.loadMusic( "victory", "musics/victorybg.it" );
	fmod.loadSound( "victory", "musics/victory.it" );

	Siam::UI::Main::CLI ui( fmod );


	return 0;
}

END_OF_MAIN()
