#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/main/maincliui.hpp"
#include "siam/inc/ui/main/mainallegroui.hpp"

<<<<<<< HEAD
void INeedPlayers( std::vector<Siam::Player>& players ) { //gets the players info

	Functions::CLI cli;
    cli.clearScreen();
	std::string nameOfPlayer;

    cli.moveCursor(10,70); //first player
	std::cout << "Entrez le nom du joueur 1 : " ;
	cli.moveCursor(12,70);
	std::cin >> nameOfPlayer;
	players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Rhinoceros ) );

    cli.moveCursor(15,70); //second player
	std::cout << "Entrez le nom du joueur 2 : " ;
	cli.moveCursor(17,70);
	std::cin >> nameOfPlayer;
	players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Elephant ) );


}


void logo() { //game logo !

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

void menuPrincipal( std::vector<Siam::Player>& players, Siam::UI::Audio::FMOD& fmod ) { //well that's the menu
	int key;

    Functions::CLI cli;
    cli.clearScreen();
    cli.setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); //set the colors right
	do {
		logo(); //display game logo
		cli.moveCursor(30,70); //go to the right spot
        std::cout << "Entrez votre choix : " ; //display the actual menu
        cli.moveCursor(32,70);
		std::cout << "1. Nouvelle Partie" ;
		cli.moveCursor(34,70);
		std::cout << "2. Sons" ;
		cli.moveCursor(36,70);
		key = cli.getKey(); //get the user's entry

		switch( key ) { //act accordingly
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
	} while( key != 27 ); //if you press escape we leave
	cli.resetColor();
}


int main() {
	std::vector<Siam::Player> players; //initialize players
	Siam::UI::Audio::FMOD fmod; //initialize music

=======
int main() {
	Siam::UI::Audio::FMOD fmod;
>>>>>>> d064672314cb83d1601f6b722d160e810cdcd54d

	fmod.loadMusic( "menu", "musics/menu.it" );
	fmod.loadMusic( "main1", "musics/main1.it" );
	fmod.loadMusic( "victory", "musics/victorybg.it" );
	fmod.loadSound( "victory", "musics/victory.it" );

<<<<<<< HEAD
	//fmod.playMusic( "menu" );


	//menuPrincipal(players,fmod);
	Siam::UI::Main::Allegro ui( fmod );
=======
	Siam::UI::Main::CLI ui( fmod );
>>>>>>> d064672314cb83d1601f6b722d160e810cdcd54d

	return 0;
}

END_OF_MAIN()
