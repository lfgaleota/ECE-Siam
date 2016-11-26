#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "inc/matrix/direction.hpp"

namespace Siam {
	class Object {
		protected:
			std::string m_nom;
			float m_force;
			Siam::Matrixs::Direction m_direction;

		public:
			Object();

			Object( std::string nom, float force, Siam::Matrixs::Direction direction = Siam::Matrixs::Direction::Left );

			float getForce();

			Siam::Matrixs::Direction getDirection() const;

			void setDirection( Siam::Matrixs::Direction direction );
	};
}


#endif // OBJECT_H_INCLUDED
