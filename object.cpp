#include "object.h"

using namespace std;

Object::Object()
		: m_nom( "" ), m_force( 0 ) {

}

Object::Object( string nom, float force )
		: m_nom( nom ), m_force( force ) {

}

Object::~Object() {

}

float Object::getForce() {
	return m_force;
}

Direction Object::getDirection() const {
	return this->m_direction;
}

void Object::setDirection( Direction direction ) {
	this->m_direction = direction;
}
