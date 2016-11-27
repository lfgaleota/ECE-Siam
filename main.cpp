#include <iostream>
#include <vector>
#include "siam/inc/matrix.hpp"
#include "siam/inc/objects/mountain.hpp"
#include "siam/inc/objects/entity.hpp"
#include "siam/inc/objects/rhinoceros.hpp"
#include "siam/inc/objects/elephant.hpp"
#include "siam/inc/player.hpp"

using namespace std;

void display( Siam::Matrix& board ) {
	auto& matrix = board.getBoard();
	Siam::Object* elem = nullptr;

	for( unsigned int j = 0; j < matrix.size(); j++ ) {
		for( unsigned int i = 0; i < matrix[ j ].size(); i++ ) {
			elem = matrix[ i ][ j ];

			if( elem != nullptr ) {
				switch( elem->getType() ) {
					case Siam::Objects::Types::Type::Mountain:
						std::cout << "M";
						break;
					case Siam::Objects::Types::Type::Rhinoceros:
						std::cout << "R";
						break;
					case Siam::Objects::Types::Type::Elephant:
						std::cout << "E";
						break;
                    case Siam::Objects::Types::Type::Object:
						break;
                    case Siam::Objects::Types::Type::Entity:
						break;
				}
				switch( elem->getDirection() ) {
					case Siam::Matrixs::Direction::Left:
						std::cout << "<";
						break;
					case Siam::Matrixs::Direction::Right:
						std::cout << ">";
						break;
					case Siam::Matrixs::Direction::Top:
						std::cout << "/";
						break;
					case Siam::Matrixs::Direction::Bottom:
						std::cout << "\\";
						break;
				}
			} else {
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

void playerchoice(Siam::Player* player1, Siam::Player* player2)
{
    bool choix ;
    cout << "vous etes plutot du genre a jouer les elephants vous non ?" << endl ;
    cout << "0:OUI 1:NON" << endl ;
    cin >> choix ;

    player1->savechoice(choix);
    player2->savechoice(!choix);

    cout << player1->getanimalchosen() << endl ;


}

int main() {
	unsigned int x = 0, y = 0;

	Siam::Objects::Mountain M1( "M", 0.9 ), M2( "M", 0.9 ), M3( "M", 0.9 ); //création des trois montagnes nécéssaires au jeu
	vector<Siam::Object*> remplir; // on va les stocker dans un vector c'est plus pratique à manipuler
	Siam::Player player1("Louis-Felix"), player2("Romain") ;

	playerchoice(&player1, &player2);

	remplir.push_back( & M1 ); //on les met effectivement dedans
	remplir.push_back( & M2 );
	remplir.push_back( & M3 );

	Siam::Matrix board( remplir ); //on initialise le terrain de jeu !

	board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Left, nullptr ), x, y );
	board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Right, nullptr ), x + 1, y ); //test d'entrée dans la matrice d'une entité
	board.add( new Siam::Objects::Rhinoceros( "R2", 1, Siam::Matrixs::Direction::Right, nullptr ), x + 2, y );
	board.add( new Siam::Objects::Elephant( "E2", 1, Siam::Matrixs::Direction::Left, nullptr ), x + 3, y );

	display( board );

	std::cout << board.getForce( 1, 0, board.getDirectionVector( Siam::Matrixs::Direction::Right ) ) << std::endl;

	board.remove( x, y ); //on enlève une pièce qui est au bord
	return 0;
}
