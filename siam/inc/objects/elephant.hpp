#ifndef _ECE_SIAM_ELEPHANT_HPP_
	#define _ECE_SIAM_ELEPHANT_HPP_

	#include "entity.hpp"

	namespace Siam {
		namespace Objects {

			class Elephant : public Entity {
				public:
					Elephant();
					Elephant( std::string nom, float force, Siam::Matrixs::Direction direction, Player* player );

					Siam::Objects::Types::Type getType();
			};

		}
	}
#endif
