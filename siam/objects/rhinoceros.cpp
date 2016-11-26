#include "../inc/objects/rhinoceros.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Rhinoceros::Rhinoceros() : Entity() {}
Rhinoceros::Rhinoceros( string nom, float force, Direction direction, Player* player ) : Entity( nom, force, direction, player ) {}

Types::Type Rhinoceros::getType() {
	return Types::Type::Rhinoceros;
}