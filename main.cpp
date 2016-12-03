#include <fstream>
#include <allegro.h>
#include "winhack.h"

#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/gamecliui.hpp"

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



int main() {
	std::vector<Siam::Player> players;

	newGame();
	INeedPlayers(players);
	Siam::Game game = Siam::Game( players );



	return 0;
}

END_OF_MAIN();