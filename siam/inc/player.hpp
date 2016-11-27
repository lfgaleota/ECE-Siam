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

				void savechoice(bool choice); //recevra le choix de l'user sous forme de vrai/faux
		};

	}
#endif
