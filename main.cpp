#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/gamecliui.hpp"
#include "cli/cli.hpp"
#include "siam/inc/ui/audio/FMOD.hpp"

void INeedPlayers( std::vector<Siam::Player>& players ) {

	Functions::CLI cli;
    cli.clearScreen();
	std::string nameOfPlayer;

    cli.moveCursor(10,70);
	std::cout << "Entrez le nom du joueur 1 : " ;
	cli.moveCursor(12,70);
	std::cin >> nameOfPlayer;
	players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Rhinoceros ) );

    cli.moveCursor(15,70);
	std::cout << "Entrez le nom du joueur 2 : " ;
	cli.moveCursor(17,70);
	std::cin >> nameOfPlayer;
	players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Elephant ) );


}

void logo() {
	std::ifstream logo( "texts/siam.txt" );

	if( logo ) {
		std::string ligne;

		while( getline( logo, ligne ) ) {
			std::cout << ligne << std::endl;
		}
	} else {
		throw std::ios_base::failure( "File not found: texts/siam.txt" );
	}
}

void menuPrincipal( std::vector<Siam::Player>& players, Siam::UI::Audio::FMOD& fmod ) {
	int key;

    Functions::CLI cli;
    cli.clearScreen();
    cli.setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	do {
		logo();
		cli.moveCursor(30,70);
        std::cout << "Entrez votre choix : " ;
        cli.moveCursor(32,70);
		std::cout << "1. Nouvelle Partie" ;
		cli.moveCursor(34,70);
		std::cout << "2. Sons" ;
		cli.moveCursor(36,70);
		key = cli.getKey();

		switch( key ) {
			case 7:
				INeedPlayers( players );
				fmod.stopMusic();
				Siam::Game( players, fmod );
				fmod.playMusic( "menu" );
				break;

			case 8:
				fmod.pauseMusic();
				break;

		}
	} while( key != 27 );
	cli.resetColor();
}


int main() {
	std::vector<Siam::Player> players;
	Siam::UI::Audio::FMOD fmod;

	fmod.loadMusic( "menu", "musics/menu.it" );
	fmod.loadMusic( "main1", "musics/main1.it" );
	fmod.loadMusic( "victory", "musics/victorybg.it" );
	fmod.loadSound( "victory", "musics/victory.it" );

	fmod.playMusic( "menu" );

	menuPrincipal(players,fmod);

	return 0;
}

END_OF_MAIN()
