#include "inc/player.hpp"
#include <iostream>

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Player::Player( string name, Siam::Objects::Types::Type animalchosen ) : m_name( name ), m_animalchosen( animalchosen ) { //overload constructor
	for( unsigned int i = 0; i < 5; i++ ) { //we need 5 pieces per player
		if( animalchosen == Types::Type::Elephant ) //check the chosen animal
			m_pieces.push( new Siam::Objects::Elephant( "E", 1, Siam::Matrixs::Direction::Right ) ); //create the right stack
		else if( animalchosen == Types::Type::Rhinoceros )
			m_pieces.push( new Siam::Objects::Rhinoceros( "R", 1, Siam::Matrixs::Direction::Left ) );
		else
			throw exceptions::invalid_object_type(); //shielding
	}
}

Siam::Objects::Types::Type Player::getAnimalChosen() const { //read access to the chosen animal
	return this->m_animalchosen;
}

std::string Player::getName() const { //read access to name attribute
	return this->m_name;
}

void Player::stockPiece( Siam::Object* piece ) {
	if( m_pieces.size() < 5 ) { //check if the stack isn't full
		m_pieces.push( piece ); //then puts the chosen piece (back) in the stack
	} else {
		throw exceptions::stack_full( "This player has already the maximum number of piecces" ); //shielding
	}
}

Object* Player::retrievePiece() {
	if( m_pieces.size() > 0 ) { //check if the stack isn't empty
		Object* obj = m_pieces.top(); //gets the first one
		m_pieces.pop(); //removes it from the stack
		return obj; //returns the piece he got
	} else {
		throw exceptions::stack_empty( "No more pieces for this player" ); //shielding
	}
}

unsigned int Player::getMountainsCount() const { //this is pretty clear
	return this->m_mountains;
}

void Player::incrementMountainsCount() { //this doesn't need any explaination
	this->m_mountains++;
}

void Player::removeRemainingObjects() {
	for( Object* obj = nullptr; !this->m_pieces.empty(); ) { //check for pieces in the stack
		obj = this->m_pieces.top(); //gets the first one
		if ( obj != nullptr ) { //if it's not null
			delete obj; //delete it
		}
		this->m_pieces.pop(); //pops it from the stack
	}
}

unsigned long Player::getRemainingObjects() const { //read access to the number of remaining objects in the player's stack
	return this->m_pieces.size();
}
