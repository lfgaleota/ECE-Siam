#include "object.h"
#include "matrix.h"
#include "entity.h"

using namespace std ;

Entity::Entity()
    : Object(), m_orientation('h'), m_player(nullptr)
{

}

Entity::Entity(string nom, float force, char orientation, Player* player)
    : Object(nom, force), m_orientation(orientation), m_player(player)
{

}

Entity::~Entity()
{

}

void Entity::setdirection(char direction)
{
    m_orientation = direction ;
}
