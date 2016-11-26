#include <iostream>
#include <vector>
#include "siam/inc/matrix.hpp"
#include "siam/inc/objects/mountain.hpp"
#include "siam/inc/objects/entity.hpp"
#include "siam/inc/objects/rhinoceros.hpp"

using namespace std;

void display( Siam::Matrix& board ) {
	for( const auto& invec : board.getBoard() ) {
		for( const auto& elem : invec ) {
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
	Siam::Objects::Rhinoceros Rhino1( "R1", 1, Siam::Matrixs::Direction::Left, nullptr ); //pas fait l'assignation d'un animal à un joueur pour le moment donc pointeur null
	vector<Siam::Object*> remplir; // on va les stocker dans un vector c'est plus pratique à manipuler

	remplir.push_back( & M1 ); //on les met effectivement dedans
	remplir.push_back( & M2 );
	remplir.push_back( & M3 );

	Siam::Matrix board( remplir ); //on initialise le terrain de jeu !

	board.add( &Rhino1, x, y ); //test d'entrée dans la matrice d'une entité

	display( board );

	board.remove( x, y ); //on enlève une pièce qui est au bord
	return 0;
}
