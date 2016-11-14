#include "object.h"
#include "mountain.h"
#include "matrix.h"

Mountain::Mountain()
    : Object()
{

}

Mountain::Mountain(string nom, float force)
    : Object(nom, force)
{

}

Mountain::~Mountain()
{

}

using namespace std ;
