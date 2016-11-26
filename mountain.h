#ifndef MOUNTAIN_H_INCLUDED
#define MOUNTAIN_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"



namespace Siam {
	namespace Objects {
		class Mountain : public Siam::Object {
			public :

				Mountain();

				Mountain( std::string nom, float force );

				//sortie du terrain
		};
	}
}


#endif // MOUNTAIN_H_INCLUDED
