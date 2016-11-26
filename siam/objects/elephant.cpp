#include "../inc/objects/elephant.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Elephant::Elephant() : Entity() {}
Elephant::Elephant( string nom, float force, Direction direction, Player* player ) : Entity( nom, force, direction, player ) {}

Types::Type Elephant::getType() {
	return Types::Type::Mountain;
}