#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <iostream>
#include <vector>
#include <string>
#include "entity.h"

using namespace std ;

class Player
{
private :

    string m_name ;
    //attribut pour le camp choisi ? string ou pointeur sur une des pieces ?

public :

    Player();
    Player(string name);
    ~Player();


};



#endif // PLAYER_H_INCLUDED
