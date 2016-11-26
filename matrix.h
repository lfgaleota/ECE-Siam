#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <string>
#include "object.h"
#include "cli/cli.hpp"
#include "inc/exceptions/exceptions.hpp"
#include "inc/matrix/direction.hpp"

using namespace std;

class Matrix {
	private :

		unsigned int m_tour;
		Object t;

		vector<vector<Object*>> m_board;

		DirectionVector getDirectionVector( Direction dir );
		inline Object* at( unsigned int x, unsigned int y );
		inline void set( unsigned int x, unsigned int y, Object* obj );

		inline Object* at( unsigned int x, unsigned int y, DirectionVector dvec );
		inline void set( unsigned int x, unsigned int y, DirectionVector dvec, Object* obj );

	public :

		Matrix( vector<Object*> remplir );

		~Matrix();

		void add( Object* A, unsigned int x, unsigned int y );

		void remove( unsigned int x, unsigned int y );

		void move( unsigned int x, unsigned int y, Direction direction );

		void orient( unsigned int x, unsigned int y, Direction direction );

};


#endif // MATRIX_H_INCLUDED
