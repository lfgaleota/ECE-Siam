#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/gamecliui.hpp"
#include "siam/inc/ui/audio/FMOD.hpp"

void INeedPlayers ( std::vector<Siam::Player>& players)
{
    std::string nameOfPlayer ;

    std::cout << "Entrez le nom du joueur 1 : " << std::endl ;
    std::cin >> nameOfPlayer ;
    players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Rhinoceros ) );

    std::cout << "Entrez le nom du joueur 2 : " << std::endl ;
    std::cin >> nameOfPlayer ;
    players.push_back( Siam::Player( nameOfPlayer, Siam::Objects::Types::Type::Elephant ) );


}

void newGame ()
{
    std::ifstream logo("C:/Users/romai/Desktop/Siam/logoSiam.txt");

    if(logo)
    {
        std::string ligne;

        while(getline(logo, ligne))
        {
            std::cout << ligne << std::endl;
        }
    }
    else
    {
        std::cout << "nope didn't work" << std::endl;
    }

    Sleep(2000);
}

void manageMusics(Siam::UI::Audio::FMOD& mediaPlayer)
{

    mediaPlayer.loadMusic("unity","C:/Users/romai/Desktop/Siam/Unity.wav");
    mediaPlayer.playMusic("unity");

}

void menuPrincipal(std::vector<Siam::Player>& players, Siam::UI::Audio::FMOD& mediaPlayer)
{
    char key;
    //CLI cli = CLI();
    int music=0 ;

    do
    {
        std::cout << "Entrez votre choix " << std::endl ;
        std::cout << "1. Nouvelle Partie" << std::endl ;
        std::cout << "2. Sons" << std::endl ;
        std::cout << "Escape pour quitter" << std::endl ;
        //key = cli.getKey();
        std::cin >> key ;

        switch(key)
        {
        case '1' :
            INeedPlayers(players);
            {
                Siam::Game game = Siam::Game( players );
            }
            break;

        case '2' :

            std::cout << "1. ON" << std::endl ;
            std::cout << "2. OFF" << std::endl ;
            std::cin >> music ;
            if(music==1)
                manageMusics(mediaPlayer);
            else
                mediaPlayer.stopMusic();


            break ;


        }
    } while(key != 27);

}



int main() {
    std::vector<Siam::Player> players;
    Siam::UI::Audio::FMOD mediaPlayer ;

    newGame();
    manageMusics(mediaPlayer);

    menuPrincipal(players,mediaPlayer);




    return 0;
}

END_OF_MAIN();
