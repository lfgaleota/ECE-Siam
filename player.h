#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <vector>
#include <string>

namespace Siam {
	class Player {
		private :

			std::string m_name;
			//attribut pour le camp choisi ? string ou pointeur sur une des pieces ?

		public :

			Player();

			Player( std::string name );

			~Player();


	};
}


#endif // PLAYER_H_INCLUDED
