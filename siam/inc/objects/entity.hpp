#ifndef _ECE_SIAM_ENTITY_HPP_
	#define _ECE_SIAM_ENTITY_HPP_

	#include <vector>
	#include <string>
	#include "../object.hpp"
	#include "../player.hpp"
	#include "../matrixs/direction.hpp"
	#include "../objects/types/type.hpp"

	namespace Siam {
		namespace Objects {

			class Entity : public Siam::Object { //inherits from object
				private:
					Player* m_player; //each entity will have a player associated

				public:
					Entity(); //default constructor
					Entity( std::string nom, float force, Siam::Matrixs::Direction direction, Player* player ); //overload constructor

					virtual Siam::Objects::Types::Type getType();//gets type of object --> useful because classes will inherit of object
			};

		}
	}
#endif
