#ifndef _ECE_SIAM_MATRIX_HPP_
	#define _ECE_SIAM_MATRIX_HPP_

	#include <vector>
	#include <string>
	#include "object.hpp"
	#include "exceptions/exceptions.hpp"
	#include "matrixs/direction.hpp"

	namespace Siam {

		class Matrix {
			private:
				unsigned int m_tour;
				Siam::Object t;

				std::vector<std::vector<Siam::Object*>> m_board;

				inline Siam::Object* at( unsigned int x, unsigned int y );
				inline void set( unsigned int x, unsigned int y, Siam::Object* obj );

				inline Siam::Object* at( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec );
				inline void set( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec, Siam::Object* obj );

				int getFrontForce( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec );
				int getBackForce( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec );

			public:
				Matrix( std::vector<Siam::Object*> remplir );
				~Matrix();

				void add( Siam::Object* A, unsigned int x, unsigned int y );
				void remove( unsigned int x, unsigned int y );

				void move( unsigned int x, unsigned int y, Siam::Matrixs::Direction direction );
				void orient( unsigned int x, unsigned int y, Siam::Matrixs::Direction direction );

				const std::vector<std::vector<Siam::Object*>>& getBoard();

				Siam::Matrixs::DirectionVector getDirectionVector( Siam::Matrixs::Direction dir );

				int getForce( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec );
		};

	}
#endif
