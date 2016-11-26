#ifndef _ECE_SIAM_DIRECTION_HPP_
#define _ECE_SIAM_DIRECTION_HPP_

enum Direction {
	Left,
	Right,
	Top,
	Bottom
};

struct DirectionVector {
	const int x;
	const int y;

	DirectionVector() : x( 0 ), y( 0 ) {}
	DirectionVector( int _x, int _y ) : x( _x ), y( _y ) {}
};

#endif
