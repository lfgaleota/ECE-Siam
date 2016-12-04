#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/gamecliui.hpp"
#include "siam/inc/ui/audio/FMOD.hpp"

void INeedPlayers( std::vector<Siam::Player>& players ) {
	std::string nameOfPlayer;

	std::cout << "Entrez le nom du joueur 1 : " << std::endl;
	std::cin >> nameOfPlayer;
	players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Rhinoceros ) );

	std::cout << "Entrez le nom du joueur 2 : " << std::endl;
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
	//CLI cli = CLI();

	do {
		logo();

		std::cout << "Entrez votre choix " << std::endl;
		std::cout << "1. Nouvelle Partie" << std::endl;
		std::cout << "2. Sons" << std::endl;
		std::cout << "Echap pour quitter" << std::endl;
		//key = cli.getKey();
		key = getch();

		switch( key ) {
			case 49:
				INeedPlayers( players );
				fmod.stopMusic();
				Siam::Game( players, fmod );
				fmod.playMusic( "menu" );
				break;

			case 50:
				fmod.pauseMusic();
				break;

		}
	} while( key != 27 );
}


int main() {
	std::vector<Siam::Player> players;
	Siam::UI::Audio::FMOD fmod;

	fmod.loadMusic( "menu", "musics/menu.ogg" );
	fmod.loadMusic( "main1", "musics/main1.ogg" );
	fmod.loadMusic( "victory", "musics/victorybg.ogg" );
	fmod.loadSound( "victory", "musics/victory.ogg" );

	fmod.playMusic( "menu" );

	logo();
	SLEEP( 2000 );

	menuPrincipal( players, fmod );


	return 0;
}

END_OF_MAIN();
