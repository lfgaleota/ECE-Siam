#ifndef _ECE_SIAM_RHINOCEROS_HPP_
	#define _ECE_SIAM_RHINOCEROS_HPP_

	#include "entity.hpp"

	namespace Siam {
		namespace Objects {

			class Rhinoceros : public Entity {
				public:
					Rhinoceros();//default constructor
					Rhinoceros( std::string nom, float force, Siam::Matrixs::Direction direction );//overload constructor

					Siam::Objects::Types::Type getType();//gets type of object --> useful because classes will inherit of object
			};

		}
	}
#endif
