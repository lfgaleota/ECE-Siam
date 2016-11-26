#include "object.h"
#include "entity.h"

using namespace std;

Entity::Entity() : Object(), m_player( nullptr ) {}
Entity::Entity( string nom, float force, Player* player ) : Object( nom, force ), m_player( player ) {}
