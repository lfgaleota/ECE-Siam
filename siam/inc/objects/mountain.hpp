#ifndef _ECE_SIAM_MOUNTAIN_HPP_
	#define _ECE_SIAM_MOUNTAIN_HPP_

	#include <vector>
	#include <string>
	#include "../object.hpp"

	namespace Siam {
		namespace Objects {

			class Mountain : public Siam::Object {
				public:
					Mountain();
					Mountain( std::string nom, float force );

					Siam::Objects::Types::Type getType();
			};

		}
	}
#endif
