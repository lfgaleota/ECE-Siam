#include "object.h"
#include "entity.h"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Entity::Entity() : Object(), m_player( nullptr ) {}
Entity::Entity( string nom, float force, Direction direction, Player* player ) : Object( nom, force, direction ), m_player( player ) {}
