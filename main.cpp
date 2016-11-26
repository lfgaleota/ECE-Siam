#include <iostream>
#include <vector>
#include "matrix.h"
#include "mountain.h"
#include "entity.h"

using namespace std;

int main() {
	unsigned int x = 0, y = 0;

	Mountain M1( "M", 0.9 ), M2( "M", 0.9 ), M3( "M", 0.9 ); //création des trois montagnes nécéssaires au jeu
	Entity Rhino1( "R1", 1, 'h', nullptr ); //pas fait l'assignation d'un animal à un joueur pour le moment donc pointeur null
	vector<Object*> remplir; // on va les stocker dans un vector c'est plus pratique à manipuler

	remplir.push_back( & M1 ); //on les met effectivement dedans
	remplir.push_back( & M2 );
	remplir.push_back( & M3 );

	Matrix board( remplir ); //on initialise le terrain de jeu !

	board.add( &Rhino1, x, y ); //test d'entrée dans la matrice d'une entité
	board.remove( x, y ); //on enlève une pièce qui est au bord
	return 0;
}
