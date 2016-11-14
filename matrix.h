#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"



using namespace std ;

class Matrix
{
private :

    int m_tour ;
    Object t ;

    vector<vector<Object*>> m_board ;

public :

    Matrix(vector<Object*> remplir);
    ~Matrix();

    void entrance(Object* A);
    void exit();
    void makeamove();
    void orient();

};



#endif // MATRIX_H_INCLUDED
