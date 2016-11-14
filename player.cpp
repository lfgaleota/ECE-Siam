#include <iostream>
#include <vector>
#include <string>
#include "entity.h"

using namespace std ;

Player::Player()
    : m_name("")
{

}

Player::Player(string name)
    : m_name(name)
{

}

Player::~Player()
{

}
