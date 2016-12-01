#include "siam/inc/game.hpp"
#include "siam/inc/ui/games/CLI.hpp"
#include "siam/inc/ui/audio/FMOD.hpp"

int main() {
	std::vector<Siam::Player> players;
	players.push_back( Siam::Player( "Louis-Felix", Siam::Objects::Types::Type::Rhinoceros ) );
	players.push_back( Siam::Player( "Romain", Siam::Objects::Types::Type::Elephant ) );

	Siam::UI::Audio::FMOD fmod = Siam::UI::Audio::FMOD();

	Siam::Game game = Siam::Game( players );

	return 0;
}

///ICI JE VAIS METTRE TOUS LES TRUCS QU'ILS FAUT CHANGER OU MODIFIER SUITE AUX TESTS

///ON NE PEUT PAS REORIENTER ET BOUGER UNE PIECE EN MEME TEMPS,LE MOUVEMENT N'EST PAS ACCEPTE
///LA VICTOIRE N'EST SANS DOUTE PAS APPELEE CAR IL N'Y A PAS D'ARRET DU JEU LORS DE LA SORTIE D'UNE MONTAGNE
