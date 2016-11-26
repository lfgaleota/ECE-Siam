#include <iostream>
#include <vector>
#include "siam/inc/matrix.hpp"
#include "siam/inc/objects/mountain.hpp"
#include "siam/inc/objects/entity.hpp"
#include "siam/inc/objects/rhinoceros.hpp"
#include "siam/inc/objects/elephant.hpp"

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

int main() {
	unsigned int x = 0, y = 0;

	Siam::Objects::Mountain M1( "M", 0.9 ), M2( "M", 0.9 ), M3( "M", 0.9 ); //création des trois montagnes nécéssaires au jeu
	vector<Siam::Object*> remplir; // on va les stocker dans un vector c'est plus pratique à manipuler

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
