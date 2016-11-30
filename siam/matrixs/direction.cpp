#include "../inc/matrixs/direction.hpp"

using namespace Siam::Matrixs;

DirectionVector::DirectionVector() : x( 0 ), y( 0 ) {}

DirectionVector::DirectionVector( int _x, int _y ) : x( _x ), y( _y ) {}

DirectionVector::DirectionVector( const DirectionVector& cpy ) : x( cpy.x ), y( cpy.y ) {}

DirectionVector operator*( int lhs, DirectionVector const& rhs ) {
	return DirectionVector( lhs * rhs.x, lhs * rhs.y );
}

DirectionVector operator*( DirectionVector const& lhs, int rhs ) {
	return DirectionVector( rhs * lhs.x, rhs * lhs.y );
}

bool operator==( DirectionVector const& lhs, DirectionVector const& rhs ) {
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}