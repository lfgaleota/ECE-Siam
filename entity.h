#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"
#include "player.h"
#include "matrix.h"

namespace Siam {
	namespace Objects {
		class Entity : public Siam::Object {
			private:
				Player* m_player;

			public:
				Entity();

				Entity( std::string nom, float force, Siam::Matrixs::Direction direction, Player* player );
		};
	}
}


#endif // ENTITY_H_INCLUDED
