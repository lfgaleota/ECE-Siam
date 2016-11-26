#ifndef MOUNTAIN_H_INCLUDED
#define MOUNTAIN_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"


using namespace std;

class Mountain : public Object {
	public :

		Mountain();
		Mountain( string nom, float force );

		//sortie du terrain
};


#endif // MOUNTAIN_H_INCLUDED
