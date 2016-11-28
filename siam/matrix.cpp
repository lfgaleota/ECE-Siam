#include "inc/matrix.hpp"

using namespace std; //inclusion of the namespaces
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Matrix::Matrix() : m_tour( 0 ), m_board( 5, vector<Siam::Object*>( 5 ) ) {
	for( unsigned int i = 0; i < 5; i++ ) {
		for( unsigned int j = 0; j < 5; j++ ) {
			if( ( i == 1 && j == 2 ) || ( i == 2 && j == 2 ) || ( i == 3 && j == 2 ) ) {
				this->set( i, j, new Mountain( "M", 0 ) );
			} else {
				this->set( i, j, nullptr );
			}
		}
	}

}

Matrix::~Matrix() { //destructor
	for( auto& invec : this->m_board ) { //also delete every Object in all the cases
		for( auto& elem : invec ) {
			if( elem != nullptr )
				delete elem;
		}
	}
}

void Matrix::add( Siam::Object* A, unsigned int x, unsigned int y ) { //add function
	if( ( x == 0 ) || ( x == 4 ) || ( y == 0 ) || ( y == 4 ) ) { //check if we are effectively on the edge of the board
		try {
			if( this->at( x, y ) == nullptr ) { // then if the chosen spot is empty we'll just fill it
				this->set( x, y, A );
			} else {
				throw Siam::exceptions::invalid_move( "Add: Already occupied" ); //else an error
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Add: Out of bound" ); //shielding
		}
	} else {
		throw Siam::exceptions::invalid_move( "Add: Not authorized" );
	}
}

Siam::Object* Matrix::remove( unsigned int x, unsigned int y ) { //remove a piece from the board
	Siam::Object* obj;

	if( ( x == 0 ) || ( x == 4 ) || ( y == 0 ) || ( y == 4 ) ) { //check if we are within the boundaries
		try {
			if( this->at( x, y ) != nullptr ) { //delete the pointer on object
				obj = this->at( x, y );
				this->set( x, y, nullptr );
				return obj;
			} else {
				throw Siam::exceptions::invalid_move( "Remove: Empty space" );
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Remove: Out of bound" ); //shielding
		}
	} else {
		throw Siam::exceptions::invalid_move( "Remove: Not authorized" );
	}
}

DirectionVector Matrix::getDirectionVector( Direction dir ) { //used to get the direction of an Object
	switch( dir ) {
		case Left:
			return DirectionVector( -1, 0 );
		case Right:
			return DirectionVector( 1, 0 );
		case Top:
			return DirectionVector( 0, -1 );
		case Bottom:
			return DirectionVector( 0, 1 );
	}

	return DirectionVector();
}

inline Siam::Object* Matrix::at( unsigned int x, unsigned int y ) { //at is a function that replaces [] with more efficiency
	return this->m_board.at( x ).at( y );
}

inline void Matrix::set( unsigned int x, unsigned int y, Siam::Object* obj ) { //places an object in a spot x,y
	if( x < m_board.size() && y < m_board.size() )
		this->m_board[ x ][ y ] = obj;
	else
		throw out_of_range( "Accessing outside the defined Matrix::Matrix" );
}

inline Siam::Object* Matrix::at( unsigned int x, unsigned int y, DirectionVector dvec ) { //surcharged version of at
	return this->m_board.at( x + dvec.x ).at( y + dvec.y );
}

inline void Matrix::set( unsigned int x, unsigned int y, DirectionVector dvec, Siam::Object* obj ) { //surcharged version of set
	if( x < m_board.size() && y < m_board.size() )
		this->m_board[ x + dvec.x ][ y + dvec.y ] = obj;
	else
		throw out_of_range( "Accessing outside the defined Matrix::Matrix" );
}

int Matrix::getForce( unsigned int x, unsigned int y, DirectionVector dvec ) {
	int forceSum = 0;

	try {
		Object* initobj = this->at( x, y );
		Object* obj;
		DirectionVector invdvec = -1 * dvec;

		if( initobj != nullptr ) {
			try {
				obj = this->at( x, y );
				for( int nb = 1; obj != nullptr; nb++, obj = this->at( x, y, nb * dvec ) ) {
					if( initobj->getType() == obj->getType() && this->getDirectionVector( obj->getDirection() ) == dvec )
						forceSum += obj->getForce();
					else if( initobj->getType() != obj->getType() && this->getDirectionVector( obj->getDirection() ) == invdvec )
						forceSum -= obj->getForce();
				}
			} catch( out_of_range e ) {}

			return forceSum;
		} else {
			throw Siam::exceptions::invalid_move( "Front force: empty space" );
		}
	} catch( out_of_range e ) {
		throw Siam::exceptions::invalid_move( "Front force: out of range" );
	}
}

void Matrix::move( unsigned int x, unsigned int y, Direction direction ) { //move a piece
	DirectionVector dvec = this->getDirectionVector( direction ); //get the direction of the piece

	if( this->at( x, y ) != nullptr ) { //if the chosen spot is not empty
		try {
			if( this->at( x, y, dvec ) == nullptr ) { //if the arrival spot is empty just make the change
				this->set( x, y, dvec, this->at( x, y ) );
				this->set( x, y, nullptr );
			} else {
				if( this->at( x, y )->getForce() == this->at( x, y, dvec )->getForce() ) { //else check for the power balance

				}
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Move: out of range" ); //shielding
		}
	}
}

void Matrix::orient( unsigned int x, unsigned int y, Direction direction ) { //reorient a piece
	try {
		this->at( x, y )->setDirection( direction ); //reorienting
	} catch( out_of_range e ) {
		throw Siam::exceptions::invalid_move( "Set direction: out of range" ); //shielding
	}
}

const std::vector<std::vector<Siam::Object*>>& Matrix::getBoard() { //read access to the board
	return m_board;
}

unsigned int Matrix::gettour() //read access to tour
{
    return m_tour ;
}

void Matrix::settour() //write access to tour -> only does tour++
{
    m_tour++ ;
}
