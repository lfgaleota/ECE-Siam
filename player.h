#ifndef _ECE_SIAM_PLAYER_HPP_
	#define _ECE_SIAM_PLAYER_HPP_

	#include <vector>
	#include <string>

	namespace Siam {

		class Player {
			private:
				std::string m_name;
				//attribut pour le camp choisi ? string ou pointeur sur une des pieces ?

			public:
				Player();
				Player( std::string name );

				~Player();
		};

	}
#endif
