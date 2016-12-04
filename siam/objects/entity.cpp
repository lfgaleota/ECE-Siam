#include "../inc/object.hpp"
#include "../inc/objects/entity.hpp"


//access via the namespaces
using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Entity::Entity() : Object() {} //default constructor
Entity::Entity( string nom, float force, Direction direction ) : Object( nom, force, direction ) {} //overload constructor


Types::Type Entity::getType() const { //read access to type
	return Types::Type::Entity;
}
