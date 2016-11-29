#include "../inc/objects/elephant.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Elephant::Elephant() : Entity() {} //default constructor
Elephant::Elephant( string nom, float force, Direction direction ) : Entity( nom, force, direction ) {} //overload constructor

Types::Type Elephant::getType() { //read access to type
	return Types::Type::Elephant;
}
