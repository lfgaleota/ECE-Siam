#include "../inc/objects/rhinoceros.hpp"

//access via the namespaces
using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Rhinoceros::Rhinoceros() : Entity() {} //default constructor
Rhinoceros::Rhinoceros( string nom, float force, Direction direction ) : Entity( nom, force, direction ) {} //overload constructor

Types::Type Rhinoceros::getType() const { //read access to type
	return Types::Type::Rhinoceros;
}
