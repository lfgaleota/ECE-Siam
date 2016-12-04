#include "../../inc/ui/main/maincliui.hpp"

using namespace Siam;
using namespace Siam::UI::Main;
using namespace Siam::UI::Audio;

CLI::CLI( Siam::UI::Audio::FMOD& fmod ) : m_fmod( fmod ) {
	menu();
}

void CLI::logo() {
	std::ifstream logoFile( "texts/siam.txt" );

	if( logoFile.is_open() ) {
		std::string ligne;
		unsigned int x = 0, y = 0;
		Functions::CLI::setOffsets( LOGO_WIDTH, 0, x, y );

		for( unsigned int i = 0; getline( logoFile, ligne ); i++ ) {
			Functions::CLI::moveCursor( i, x );
			std::cout << ligne;
		}
	} else {
		throw std::ios_base::failure( "File not found: texts/siam.txt" );
	}
}

void CLI::menu() {
	std::vector<std::string> choices = {
		"Jouer",
	    "Sons",
	    "Quitter"
	};
	this->m_cli.clearScreen();
	Functions::CLIs::Menu* menu;

	this->m_fmod.playMusic( "menu" );

	for( bool loop = true; loop; ) {
		menu = new Functions::CLIs::Menu( "", choices, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY, LOGO_HEIGHT + 1, CLI::logo );

		switch( menu->getChoice() ) {
			case 1:
				askForPlayers();
				this->m_fmod.stopMusic();
				Siam::Game( this->m_players, this->m_fmod );
				this->m_fmod.playMusic( "menu" );
				break;

			case 2:
				if( this->m_fmod.getMasterVolume() > 0 ) {
					this->m_fmod.setMasterVolume( 0 );
				} else {
					this->m_fmod.setMasterVolume( 1.0f );
				}
				break;

			case 3:
				loop = false;
				break;

			default:
				break;
		}

		delete menu;
	}
}

void CLI::askForPlayers() {
	this->m_players.clear();
	std::string nameOfPlayer;

	this->m_cli.moveCursor(10,70);
	std::cout << "Entrez le nom du joueur 1 : " ;
	this->m_cli.moveCursor(12,70);
	std::cin >> nameOfPlayer;
	this->m_players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Rhinoceros ) );

	this->m_cli.moveCursor(15,70);
	std::cout << "Entrez le nom du joueur 2 : " ;
	this->m_cli.moveCursor(17,70);
	std::cin >> nameOfPlayer;
	this->m_players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Elephant ) );
}