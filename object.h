#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std ;

class Object
{
private :

    string m_nom ;
    float m_force ;

public :

    Object();
    Object(string nom, float force);
    ~Object();

    //méthode de déplacement
};



#endif // OBJECT_H_INCLUDED
