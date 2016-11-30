#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/CLI.hpp"

int main() {
	std::vector<Siam::Player> players;
	players.push_back( Siam::Player( "Louis-Felix", Siam::Objects::Types::Type::Rhinoceros ) );
	players.push_back( Siam::Player( "Romain", Siam::Objects::Types::Type::Elephant ) );


	Siam::Game game = Siam::Game( players );

	return 0;
}
