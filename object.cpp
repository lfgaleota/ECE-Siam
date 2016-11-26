#include "object.h"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;

Object::Object()
		: m_nom( "" ), m_force( 0 ) {

}

Object::Object( string nom, float force, Siam::Matrixs::Direction direction )
		: m_nom( nom ), m_force( force ), m_direction( direction ) {

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
