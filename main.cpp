#include <iostream>
#include <vector>
#include "matrix.h"
#include "object.h"
#include "mountain.h"
#include "entity.h"
#include "player.h"

using namespace std;

int main()
{
    Mountain M1("M",0.9), M2("M",0.9), M3("M",0.9) ; //cr�ation des trois montagnes n�c�ssaires au jeu
    Entity Rhino1("R1",1,'h', nullptr); //pas fait l'assignation d'un animal � un joueur pour le moment donc pointeur null
    vector<Object*> remplir ; // on va les stocker dans un vector c'est plus pratique � manipuler

    remplir.push_back(&M1); //on les met effectivement dedans
    remplir.push_back(&M2);
    remplir.push_back(&M3);

    Matrix board(remplir) ; //on initialise le terrain de jeu !

    board.entrance(&Rhino1); //test d'entr�e dans la matrice d'une entit�
    board.exit(); //on enl�ve une pi�ce qui est au bord
    return 0;
}
