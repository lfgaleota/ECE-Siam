#include "inc/player.hpp"
#include <iostream>

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Player::Player( string name, Siam::Objects::Types::Type animalchosen ) : m_name( name ), m_animalchosen( animalchosen ) {
	for( unsigned int i = 0; i < 5; i++ ) {
		if( animalchosen == Types::Type::Elephant )
			m_pieces.push( new Siam::Objects::Elephant( "E", 1, Siam::Matrixs::Direction::Right ) );
		else if( animalchosen == Types::Type::Rhinoceros )
			m_pieces.push( new Siam::Objects::Rhinoceros( "R", 1, Siam::Matrixs::Direction::Left ) );
		else
			throw exceptions::invalid_object_type();
	}
}

Player::~Player() {

}

Siam::Objects::Types::Type Player::getAnimalChosen() {
	return m_animalchosen;
}

std::string Player::getName() {
	return m_name;
}

void Player::stockPiece( Siam::Object* piece ) {
	if( m_pieces.size() < 5 ) {
		m_pieces.push( piece );
	} else {
		throw exceptions::stack_full( "This player has already the maximum number of piecces" );
	}
}

Object* Player::retrievePiece() {
	if( m_pieces.size() > 0 ) {
		Object* obj = m_pieces.top();
		m_pieces.pop();
		return obj;
	} else {
		throw exceptions::stack_empty( "No more pieces for this player" );
	}
}
