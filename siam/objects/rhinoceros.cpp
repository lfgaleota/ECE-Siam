#include "../inc/objects/rhinoceros.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Rhinoceros::Rhinoceros() : Entity() {}
Rhinoceros::Rhinoceros( string nom, float force, Direction direction ) : Entity( nom, force, direction ) {}

Types::Type Rhinoceros::getType() {
	return Types::Type::Rhinoceros;
}