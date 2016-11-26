#ifndef _ECE_SIAM_DIRECTION_HPP_
#define _ECE_SIAM_DIRECTION_HPP_

namespace Siam {
	namespace Matrixs {

		enum Direction {
			Left,
			Right,
			Top,
			Bottom
		};

		struct DirectionVector {
			const int x;
			const int y;

			DirectionVector();
			DirectionVector( int _x, int _y );
		};

	}
}

Siam::Matrixs::DirectionVector operator*( int lhs, Siam::Matrixs::DirectionVector& rhs );
Siam::Matrixs::DirectionVector operator*( Siam::Matrixs::DirectionVector& lhs, int rhs );
#endif
