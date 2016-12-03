#include "inc/object.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Object::Object() //default constructor
		: m_nom( "" ), m_force( 0 ) {

}

Object::Object( string nom, float force, Siam::Matrixs::Direction direction ) //overload constructor
		: m_nom( nom ), m_force( force ), m_direction( direction ) {

}

Object::~Object()
{

}

float Object::getForce() const { //read access to force
	return m_force;
}

Direction Object::getDirection() const { //read access to direction
	return this->m_direction;
}

void Object::setDirection( Direction direction ) { //write access to direction
	this->m_direction = direction;
}

Types::Type Object::getType() const { //read access to type
	return Types::Type::Object;
}
