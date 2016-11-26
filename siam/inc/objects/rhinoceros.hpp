#ifndef _ECE_SIAM_RHINOCEROS_HPP_
	#define _ECE_SIAM_RHINOCEROS_HPP_

	#include "entity.hpp"

	namespace Siam {
		namespace Objects {

			class Rhinoceros : public Entity {
				public:
					Rhinoceros();
					Rhinoceros( std::string nom, float force, Siam::Matrixs::Direction direction, Player* player );

					Siam::Objects::Types::Type getType();
			};

		}
	}
#endif
