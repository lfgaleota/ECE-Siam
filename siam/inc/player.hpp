#ifndef _ECE_SIAM_PLAYER_HPP_
	#define _ECE_SIAM_PLAYER_HPP_

	#include <vector>
	#include <string>
	#include "../inc/object.hpp"

	namespace Siam {

		class Player {
			private:
				std::string m_name;
				Siam::Objects::Types::Type m_animalchosen;

			public:
				Player( std::string name, Siam::Objects::Types::Type animalchosen );

				~Player();

				Siam::Objects::Types::Type getAnimalChosen(); //pour faire un test ça juste
				std::string getName();
		};

	}
#endif
