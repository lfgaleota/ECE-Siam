#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "object.h"
#include "cli/cli.hpp"



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

    void entrance(Object* A, int x, int y);
    void exit(int x, int y);
    void makeamove(int x, int y, char direction);
    void orient(int x, int y, char direction);

};



#endif // MATRIX_H_INCLUDED
