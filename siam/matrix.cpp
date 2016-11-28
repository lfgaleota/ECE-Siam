#include "inc/matrix.hpp"

using namespace std; //inclusion of the namespaces
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

<<<<<<< HEAD
Matrix::Matrix( vector<Siam::Object*> remplir ) //constructor
		: m_tour( 0 ), m_board( 5, vector<Siam::Object*>( 5 ) ) { //dimensions initialization -> vector<vector<object*>(dimension1, vector<object*> (dimension2))
	unsigned int k = 0;

	for( unsigned int i = 0; i < 5; i++ ) { //fill it up !
		for( unsigned int j = 0; j < 5; j++ ) {
			if( ( i == 1 && j == 2 ) || ( i == 2 && j == 2 ) || ( i == 3 && j == 2 ) ) {
				this->set( i, j, remplir[ k ] );
				k++;

			} else {
				this->set( i, j, nullptr ); //if this is not a mountain case, initiate at nullptr

=======
Matrix::Matrix() : m_tour( 0 ), m_board( 5, vector<Siam::Object*>( 5 ) ) {
	for( unsigned int i = 0; i < 5; i++ ) {
		for( unsigned int j = 0; j < 5; j++ ) {
			if( ( i == 1 && j == 2 ) || ( i == 2 && j == 2 ) || ( i == 3 && j == 2 ) ) {
				this->set( i, j, new Mountain( "M", 0 ) );
			} else {
				this->set( i, j, nullptr );
>>>>>>> 5e0340df4381d8a13fd27557d9aa34ae94243a81
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

void Matrix::remove( unsigned int x, unsigned int y ) {
	if( ( x == 0 ) || ( x == 4 ) || ( y == 0 ) || ( y == 4 ) ) {
		try {
			if( this->at( x, y ) != nullptr ) {
				this->set( x, y, nullptr );
			} else {
				throw Siam::exceptions::invalid_move( "Remove: Empty space" );
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Remove: Out of bound" );
		}
	} else {
		throw Siam::exceptions::invalid_move( "Remove: Not authorized" );
	}
}

DirectionVector Matrix::getDirectionVector( Direction dir ) {
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

inline Siam::Object* Matrix::at( unsigned int x, unsigned int y ) {
	return this->m_board.at( x ).at( y );
}

inline void Matrix::set( unsigned int x, unsigned int y, Siam::Object* obj ) {
	if( x < m_board.size() && y < m_board.size() )
		this->m_board[ x ][ y ] = obj;
	else
		throw out_of_range( "Accessing outside the defined Matrix::Matrix" );
}

inline Siam::Object* Matrix::at( unsigned int x, unsigned int y, DirectionVector dvec ) {
	return this->m_board.at( x + dvec.x ).at( y + dvec.y );
}

inline void Matrix::set( unsigned int x, unsigned int y, DirectionVector dvec, Siam::Object* obj ) {
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

void Matrix::move( unsigned int x, unsigned int y, Direction direction ) {
	DirectionVector dvec = this->getDirectionVector( direction );

	if( this->at( x, y ) != nullptr ) {
		try {
			if( this->at( x, y, dvec ) == nullptr ) {
				this->set( x, y, dvec, this->at( x, y ) );
				this->set( x, y, nullptr );
			} else {
				if( this->at( x, y )->getForce() == this->at( x, y, dvec )->getForce() ) {

				}
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Move: out of range" );
		}
	}
}

void Matrix::orient( unsigned int x, unsigned int y, Direction direction ) {
	//reçoit des coordonnées et une direction
	//prend l'objet à ces coordonnées et modifie sa direction comme il faut.
	try {
		this->at( x, y )->setDirection( direction );
	} catch( out_of_range e ) {
		throw Siam::exceptions::invalid_move( "Set direction: out of range" );
	}
}

const std::vector<std::vector<Siam::Object*>>& Matrix::getBoard() {
	return m_board;
}

unsigned int Matrix::gettour()
{
    return m_tour ;
}

void Matrix::settour()
{
    m_tour++ ;
}
