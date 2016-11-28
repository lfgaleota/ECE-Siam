#ifndef _ECE_SIAM_MATRIX_HPP_
	#define _ECE_SIAM_MATRIX_HPP_

	#include <vector>
	#include <string>
	#include "object.hpp"
	#include "exceptions/exceptions.hpp"
	#include "matrixs/direction.hpp"
	#include "objects/mountain.hpp"

	namespace Siam {

		class Matrix {
			private:
				std::vector<std::vector<Siam::Object*>> m_board; //game matrix

				inline Siam::Object* at( unsigned int x, unsigned int y ); // returns references on coordinates. Also checks against bounds
				inline void set( unsigned int x, unsigned int y, Siam::Object* obj ); //Places object at given coordinates. (only if possible)

				inline Siam::Object* at( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec ); //surcharged version of at --> includes direction vector
				inline void set( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec, Siam::Object* obj ); //surcharged version of set --> includes direction vector

			public:
				Matrix();
				virtual ~Matrix(); //destructor

				void add( Siam::Object* A, unsigned int x, unsigned int y ); //add a piece on the board at x,y spot -> only if possible
				Siam::Object* remove( unsigned int x, unsigned int y ); //removes a piece from the board. -> only if possible

				Siam::Object* move( unsigned int x, unsigned int y, Siam::Matrixs::Direction direction ); //moves if the spot is free, else checks the strength front and back and moves or not accordingly
				void orient( unsigned int x, unsigned int y, Siam::Matrixs::Direction direction ); //only modifies the direction of a piece on the board.

				const std::vector<std::vector<Siam::Object*>>& getBoard(); //read access to board

				Siam::Matrixs::DirectionVector getDirectionVector( Siam::Matrixs::Direction dir ); //gets direction of the object (read access)

				int getForce( unsigned int x, unsigned int y, Siam::Matrixs::DirectionVector dvec ); //returns sum of frontforce and backforce
				Siam::Objects::Types::Type getType( unsigned int x, unsigned int y);
		};

	}
#endif
