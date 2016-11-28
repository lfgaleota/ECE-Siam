#include "../inc/objects/elephant.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Elephant::Elephant() : Entity() {}
Elephant::Elephant( string nom, float force, Direction direction ) : Entity( nom, force, direction ) {}

Types::Type Elephant::getType() {
	return Types::Type::Elephant;
}