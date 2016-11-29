#include "../inc/object.hpp"
#include "../inc/objects/entity.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Entity::Entity() : Object() {} //default constructor
Entity::Entity( string nom, float force, Direction direction ) : Object( nom, force, direction ) {} //overload constructor


Types::Type Entity::getType() { //read access to type
	return Types::Type::Entity;
}
