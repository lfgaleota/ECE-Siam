#include "../inc/matrixs/direction.hpp"

using namespace Siam::Matrixs;

DirectionVector::DirectionVector() : x( 0 ), y( 0 ) {} //default constructor

DirectionVector::DirectionVector( int _x, int _y ) : x( _x ), y( _y ) {} //overload constructor

DirectionVector::DirectionVector( const DirectionVector& cpy ) : x( cpy.x ), y( cpy.y ) {} //copy constructor

DirectionVector operator*( int lhs, DirectionVector const& rhs ) { //overload operator *
	return DirectionVector( lhs * rhs.x, lhs * rhs.y );
}

DirectionVector operator*( DirectionVector const& lhs, int rhs ) { //overload operator *
	return DirectionVector( rhs * lhs.x, rhs * lhs.y );
}

bool operator==( DirectionVector const& lhs, DirectionVector const& rhs ) { //overload operator ==
	return ( lhs.x == rhs.x && lhs.y == rhs.y );
}
