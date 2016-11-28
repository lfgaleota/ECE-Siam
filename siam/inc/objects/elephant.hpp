#ifndef _ECE_SIAM_ELEPHANT_HPP_
	#define _ECE_SIAM_ELEPHANT_HPP_

	#include "entity.hpp"

	namespace Siam {
		namespace Objects {

			class Elephant : public Entity {
				public:
					Elephant(); //default constructor
					Elephant( std::string nom, float force, Siam::Matrixs::Direction direction );//overload constructor

					Siam::Objects::Types::Type getType();//gets type of object --> useful because classes will inherit of object
			};

		}
	}
#endif
