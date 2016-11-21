#include "matrix.h"
#include "mountain.h"
#include "cli/cli.hpp"

using namespace std ;

Matrix::Matrix(vector<Object*> remplir)
    : m_tour(0), m_board(5, vector<Object*> (5))
{
    int k=0 ;

    for(int i=0; i<5 ; i++)
    {
        for(int j=0; j<5 ; j++)
        {
            if((i==1&&j==2)||(i==2&&j==2)||(i==3&&j==2))
            {
                m_board[i][j] = remplir[k];
                k++ ;
                //cout << 'X' ;
            }
            else
            {
                m_board[i][j] = new Mountain("  ", 0.9);
                //cout << 'A' ;
            }
        }
        //cout << endl ;
    }

}

Matrix::~Matrix()
{

}

void Matrix::entrance(Object* A, int x, int y)
{

    if((x==0)||(x==4)||(y==0)||(y==4))
    {
        m_board[x][y]= A ;
    } else

        //on affiche un message d'erreur
        cout << "pas le droit ici" << endl ;
}

void Matrix::exit(int x, int y)
{

    if((x==0)||(x==4)||(y==0)||(y==4))
    {
        m_board[x][y]= nullptr ;
    } else

        //on affiche un message d'erreur
        cout << "pas le droit ici" << endl ;


}

void Matrix::makeamove(int x, int y, char direction) //reçoit des coordonnées et une direction de déplacement
{

    if(direction == 'o')
    {
        if(m_board[x-1][y]==nullptr)
        {
            m_board[x-1][y] = m_board[x][y] ;
            m_board[x][y]= nullptr ;
        }else
        {
            if(m_board[x][y]->getforce()==m_board[x-1][y]->getforce()) //la je compare avec la première case la plus proche dans la direction de mouvement, il faut que je le fasse pour les cases derrière aussi
            {

            }
        }
    }

    if(direction == 'l')
    {
        if(m_board[x+1][y]==nullptr)
        {
            m_board[x+1][y] = m_board[x][y] ;
            m_board[x][y]= nullptr ;
        }
    }

    if(direction == 'k')
    {
        if(m_board[x][y-1]==nullptr)
        {
            m_board[x][y-1] = m_board[x][y] ;
            m_board[x][y]= nullptr ;
        }
    }

    if(direction == 'm')
    {
        if(m_board[x][y+1]==nullptr)
        {
            m_board[x][y+1] = m_board[x][y] ;
            m_board[x][y]= nullptr ;
        }
    }


}

void Matrix::orient(int x, int y, char direction)
{
    //reçoit des coordonnées et une direction
    //prend l'objet à ces coordonnées et modifie sa direction comme il faut.

    m_board[x][y]->setdirection(direction);
}
