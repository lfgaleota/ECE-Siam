#ifndef _ECE_SIAM_PLAYER_HPP_
	#define _ECE_SIAM_PLAYER_HPP_

	#include <vector>
	#include <string>
	#include <stack>
	#include "../inc/exceptions/exceptions.hpp"
	#include "../inc/object.hpp"
	#include "../inc/objects/elephant.hpp"
	#include "../inc/objects/rhinoceros.hpp"

	namespace Siam {

		class Player {
			private:
				std::string m_name;
				Siam::Objects::Types::Type m_animalchosen;
				std::stack<Siam::Object*> m_pieces;

			public:
				Player( std::string name, Siam::Objects::Types::Type animalchosen );
				~Player();

				void stockPiece( Siam::Object* piece );
				Siam::Object* retrievePiece();

				Siam::Objects::Types::Type getAnimalChosen(); //pour faire un test ça juste
				std::string getName();
		};

	}
#endif
