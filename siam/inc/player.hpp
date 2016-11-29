#ifndef _ECE_SIAM_PLAYER_HPP_
	#define _ECE_SIAM_PLAYER_HPP_

	#include <vector>
	#include <string>
	#include <stack>
	#include "../inc/exceptions/exceptions.hpp"
	#include "../inc/object.hpp"
	#include "../inc/objects/elephant.hpp"
	#include "../inc/objects/rhinoceros.hpp"

	namespace Siam { //in the namespace Siam

		class Player { //player Class
			private: //attributes
				std::string m_name;
				Siam::Objects::Types::Type m_animalchosen;
				std::stack<Siam::Object*> m_pieces;
				unsigned int m_mountains = 0;

			public: //methodes
				Player( std::string name, Siam::Objects::Types::Type animalchosen ); //we only need an overload constructor because there are no pointers in the class

				void stockPiece( Siam::Object* piece ); //allows to stock the piece type of the player -> in a stack of maximum 5 for now
				Siam::Object* retrievePiece(); // gets a piece from the stack of pieces until there are 5 on the board

				void incrementMountainsCount(); //number of mountains you pushed
				unsigned int getMountainsCount() const;

				Siam::Objects::Types::Type getAnimalChosen() const; //is it useless now ?
				std::string getName() const; //this is not i think

				unsigned long getRemainingObjects() const;
				void removeRemainingObjects(); //empty the stack
		};

	}
#endif
