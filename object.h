#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "inc/matrix/direction.hpp"

using namespace std;

class Object {
	protected:
		string m_nom;
		float m_force;
		Direction m_direction;

	public:
		Object();
		Object( string nom, float force );

		float getForce();

		Direction getDirection() const;
		void setDirection( Direction direction );
};


#endif // OBJECT_H_INCLUDED
