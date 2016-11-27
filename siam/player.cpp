#include "inc/player.hpp"
#include <iostream>

using namespace std;
using namespace Siam;

Player::Player()
    : m_name( "" ) {

}

Player::Player( string name )
    : m_name( name ) {

}

Player::~Player() {

}

void Player::savechoice(bool choice)
{

    if(choice == 0 || choice == 1)
    {
        if(choice == 0)
        {
            m_animalchosen = "Elephant" ;
        }
        if(choice == 1)
        {
            m_animalchosen = "Rhinoceros" ;
        }

    } else

        cout << "Error : wrong value for choice" << endl ;

}
