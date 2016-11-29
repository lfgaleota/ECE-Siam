#include "../inc/objects/rhinoceros.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Rhinoceros::Rhinoceros() : Entity() {} //default constructor
Rhinoceros::Rhinoceros( string nom, float force, Direction direction ) : Entity( nom, force, direction ) {} //overload constructor

Types::Type Rhinoceros::getType() { //read access to type
	return Types::Type::Rhinoceros;
}
