#include "matrix.h"
#include "mountain.h"

using namespace std ;

Matrix::Matrix(vector<Object*> remplir)
    : m_tour(0), m_board(5, vector<Object*> (5))
{
    Mountain vide("  ", 0.9);
    int k=0 ;

    for(int i=0; i<5 ; i++)
    {
        for(int j=0; j<5 ;j++)
        {
            if((i==1&&j==2)||(i==2&&j==2)||(i==3&&j==2))
            {
                 m_board[i][j] = remplir[k];
                k++ ;
                //cout << 'X' ;
            }
            else
            {
                m_board[i][j] = &vide ;
                //cout << 'A' ;
            }
        }
        //cout << endl ;
    }

}

Matrix::~Matrix()
{

}

void Matrix::entrance(Object* A)
{
    //il faudra rajouter un param�tre pour recevoir la case choisie par l'utilisateur qui sera dans une m�thode d'affichage !
    //ici je vais juste la simuler

    int x=0, y=0 ;

    if((x=0)||(x=4)||(y=0)||(y=4))
    {
        m_board[x][y]= A ;
    }else

        //on affiche un message d'erreur
        cout << "pas le droit ici" << endl ;
}

void Matrix::exit()
{
    //on ajoutera des param�tres de coordonn�es (la position du curseur) pour savoir lequel enlever ?

    int x=0, y=0 ;

    if((x=0)||(x=4)||(y=0)||(y=4))
    {
        m_board[x][y]= nullptr ;
    }else

        //on affiche un message d'erreur
        cout << "pas le droit ici" << endl ;


}

void Matrix::makeamove()
{
    //on parcourt � la recherche de la position du curseur
    //une fois trouv� on "enregistre" le pointeur sur objet de la case en question
    //on demande � l'utilisateur quel mouvement faire
    //on lui demande si il veut changer l'orientation : si oui on appelle orient(), sinon rien
    //on v�rifie si il y a pouss�e ou non, et si on peut ou pas en fonction des rapport de force
    //si il n'y a pas pouss�e on "d�place" le pointeur � la case voulue
    //si il y a pouss�e on d�place la pi�ce pouss�e sur sa nouvelle position puis la pi�ce du joueur sur la case de la pi�ce pouss�e.
    //on passe un nouveau tour
}

void orient()
{
    //on parcourt � la recherche de la position du curseur
    //une fois trouv� on demande � l'user la nouvelle direction
    //on l'enregistre dans l'objet en cours d'utilisation
    //on passe le tour
}
