#include "inc/matrix.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Matrixs;

Matrix::Matrix( vector<Siam::Object*> remplir )
		: m_tour( 0 ), m_board( 5, vector<Siam::Object*>( 5 ) ) {
	unsigned int k = 0;

	for( unsigned int i = 0; i < 5; i++ ) {
		for( unsigned int j = 0; j < 5; j++ ) {
			if( ( i == 1 && j == 2 ) || ( i == 2 && j == 2 ) || ( i == 3 && j == 2 ) ) {
				this->set( i, j, remplir[ k ] );
				k++;
				//cout << 'X' ;
			} else {
				this->set( i, j, nullptr ); //new Mountain( "  ", 0.9 ); --> du coup on fait pas ça on va faire un NULL plutot
				//cout << 'A' ;
			}
		}
		//cout << endl ;
	}

}

Matrix::~Matrix() {
	for( auto& invec : this->m_board ) {
		for( auto& elem : invec ) {
			if( elem != nullptr )
				delete elem;
		}
	}
}

void Matrix::add( Siam::Object* A, unsigned int x, unsigned int y ) {
	if( ( x == 0 ) || ( x == 4 ) || ( y == 0 ) || ( y == 4 ) ) {
		try {
			if( this->at( x, y ) == nullptr ) {
				this->set( x, y, A );
			} else {
				throw Siam::exceptions::invalid_move( "Add: Already occupied" );
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Add: Out of bound" );
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

int Matrix::getBackForce( unsigned int x, unsigned int y, DirectionVector dvec ) {
	int forceSum = 0;

	try {
		Object* initobj = this->at( x, y );

		Object* obj = initobj;
		DirectionVector invdvec = -1 * dvec;

		if( initobj != nullptr ) {
			try {
				for( int nb = 0; obj != nullptr && initobj->getType() == obj->getType(); nb++, obj = this->at( x, y,
				                                                                                               nb *
				                                                                                               invdvec ) )
					if( this->getDirectionVector( obj->getDirection() ) == dvec )
						forceSum += obj->getForce();
			} catch( out_of_range e ) {}

			return forceSum;
		} else {
			throw Siam::exceptions::invalid_move( "Back force: empty space" );
		}
	} catch( out_of_range e ) {
		throw Siam::exceptions::invalid_move( "Back force: out of range" );
	}
}

int Matrix::getFrontForce( unsigned int x, unsigned int y, DirectionVector dvec ) {
	int forceSum = 0;

	try {
		Object* initobj = this->at( x, y );
		Object* obj;
		DirectionVector invdvec = -1 * dvec;

		if( initobj != nullptr ) {
			try {
				obj = this->at( x, y, dvec );
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

int Matrix::getForce( unsigned int x, unsigned int y, DirectionVector dvec ) {
	return this->getBackForce( x, y, dvec ) + this->getFrontForce( x, y, dvec );
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
