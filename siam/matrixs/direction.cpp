#include "../inc/matrixs/direction.hpp"

using namespace Siam::Matrixs;

DirectionVector::DirectionVector() : x( 0 ), y( 0 ) {}

DirectionVector::DirectionVector( int _x, int _y ) : x( _x ), y( _y ) {}

DirectionVector operator*( int lhs, DirectionVector& rhs ) {
	return DirectionVector( lhs * rhs.x, lhs * rhs.y );
}

DirectionVector operator*( DirectionVector& lhs, int rhs ) {
	return DirectionVector( rhs * lhs.x, rhs * lhs.y );
}

bool operator==( DirectionVector const& lhs, DirectionVector const& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}