#include "inc/player.hpp"
#include <iostream>

using namespace std;
using namespace Siam;

Player::Player( string name, Siam::Objects::Types::Type animalchosen ) : m_name( name ), m_animalchosen( animalchosen ) {

}

Player::~Player() {

}

Siam::Objects::Types::Type Player::getAnimalChosen() {
	return m_animalchosen;
}

std::string Player::getName() {
	return m_name;
}