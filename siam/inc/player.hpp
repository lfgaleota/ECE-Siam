#ifndef _ECE_SIAM_PLAYER_HPP_
	#define _ECE_SIAM_PLAYER_HPP_

	#include <vector>
	#include <string>
	#include "../inc/object.hpp"

	namespace Siam {

		class Player {
			private:
				std::string m_name;
				std::string m_animalchosen ;

			public:
				Player();
				Player( std::string name );

				~Player();

				void saveChoice( bool choice ); //recevra le choix de l'user sous forme de vrai/faux
				std::string getAnimalChosen(); //pour faire un test ça juste
				std::string getName();
				void setname(std::string name);
		};

	}
#endif
