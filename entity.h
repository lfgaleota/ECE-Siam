#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"
#include "player.h"
#include "matrix.h"

using namespace std;

class Entity : public Object {
	private :
		Player* m_player;

	public :
		Entity();
		Entity( string nom, float force, Player* player );
};


#endif // ENTITY_H_INCLUDED
