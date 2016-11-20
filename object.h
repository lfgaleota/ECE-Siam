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

    float getforce();
    virtual void setdirection(char direction);
};



#endif // OBJECT_H_INCLUDED
