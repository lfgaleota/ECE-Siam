#ifndef _ECE_SIAM_DIRECTION_HPP_
#define _ECE_SIAM_DIRECTION_HPP_

namespace Siam { //in the namespace Siam
	namespace Matrixs { //in the namespace matrix

		enum Direction { //directions enumeration
			Left,
			Right,
			Up,
			Down
		};

		struct DirectionVector { //building the direction vector
			const int x;
			const int y;

			DirectionVector();
			DirectionVector( int _x, int _y );
		};

	}
}

Siam::Matrixs::DirectionVector operator*( int lhs, Siam::Matrixs::DirectionVector& rhs );
Siam::Matrixs::DirectionVector operator*( Siam::Matrixs::DirectionVector& lhs, int rhs );
bool operator==( Siam::Matrixs::DirectionVector const& lhs, Siam::Matrixs::DirectionVector const& rhs );
#endif
