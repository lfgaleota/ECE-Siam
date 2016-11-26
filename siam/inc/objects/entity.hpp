#ifndef _ECE_SIAM_ENTITY_HPP_
	#define _ECE_SIAM_ENTITY_HPP_

	#include <vector>
	#include <string>
	#include "../object.hpp"
	#include "../player.hpp"
	#include "../matrixs/direction.hpp"

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
#endif
