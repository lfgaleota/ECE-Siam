#ifndef _ECE_SIAM_MOUNTAIN_HPP_
	#define _ECE_SIAM_MOUNTAIN_HPP_

	#include <vector>
	#include <string>
	#include "../object.hpp"

	namespace Siam { //in the namespace Siam
		namespace Objects { //in the namespace Objects

			class Mountain : public Siam::Object { //inherits from object
				public:
					Mountain(); //default constructor
					Mountain( std::string nom, float force ); //overload constructor

					Siam::Objects::Types::Type getType() const;//gets type of object --> useful because classes will inherit of object
			};

		}
	}
#endif
