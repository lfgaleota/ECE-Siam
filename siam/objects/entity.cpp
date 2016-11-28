#include "../inc/object.hpp"
#include "../inc/objects/entity.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Entity::Entity() : Object() {}
Entity::Entity( string nom, float force, Direction direction ) : Object( nom, force, direction ) {}


Types::Type Entity::getType() {
	return Types::Type::Entity;
}