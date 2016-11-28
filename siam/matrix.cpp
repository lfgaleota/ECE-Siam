#include "inc/matrix.hpp"

using namespace std; //inclusion of the namespaces
using namespace Siam;
using namespace Siam::Matrixs;
using namespace Siam::Objects;

Matrix::Matrix() : m_board( 5, vector<Siam::Object*>( 5 ) ) {
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
		case Up:
			return DirectionVector( 0, -1 );
		case Down:
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
		throw out_of_range( "Accessing outside the defined matrix" );
}

inline Siam::Object* Matrix::at( unsigned int x, unsigned int y, DirectionVector dvec ) { //surcharged version of at
	return this->m_board.at( x + dvec.x ).at( y + dvec.y );
}

inline void Matrix::set( unsigned int x, unsigned int y, DirectionVector dvec, Siam::Object* obj ) { //surcharged version of set
	if( x < m_board.size() && y < m_board.size() )
		this->m_board[ x + dvec.x ][ y + dvec.y ] = obj;
	else
		throw out_of_range( "Accessing outside the defined matrix" );
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

Object* Matrix::move( unsigned int x, unsigned int y, Direction direction ) { //move a piece
	DirectionVector dvec = this->getDirectionVector( direction ); //get the direction of the piece
	Object *obj, *ejectedobj = nullptr;
	int nb = 0;

	if( this->at( x, y ) != nullptr ) { //if the chosen spot is not empty
		try {
			if( this->at( x, y, dvec ) == nullptr ) { //if the arrival spot is empty just make the change
				this->set( x, y, dvec, this->at( x, y ) );
				this->set( x, y, nullptr );
			} else {
				if( this->getForce( x, y, dvec ) > 0 ) {
					// On parcourt le tableau dans la direction de déplacement jusqu'à tomber sur du vide OU sortir du tableau
					try {
						obj = this->at( x, y );
						for( nb = 0; obj != nullptr; nb++, obj = this->at( x, y, nb * dvec ) ) {}
					} catch( out_of_range e ) {}

					// Maintenant nb contient le nombre de fois qu'on se déplace pour atteindre la prochaine case vide ou sortir du tableau
					// On parcourt alors le tableau en sens inverse
					for( ; nb > 0 ; nb-- ) {
						try {
							// On intervertie l'objet en cours et celui à côté dans le sens opposé au déplacement
							obj = this->at( x, y, nb * dvec );
							this->set( x, y, nb * dvec, this->at( x, y, ( nb - 1 ) * dvec ) );
							this->set( x, y, ( nb - 1 ) * dvec, obj );
						} catch( out_of_range e ) {
							// On est en dehors! On va donc retourner l'object

							// Si on a déjà un objet à éjecter en attente
							if( ejectedobj != nullptr )
								throw exceptions::invalid_move( "Ejecting more than one piece at a time." ); // Ce n'est pas sensé arriver! On arrête tout.

							// Sinon on stocke l'objet à éjecter
							ejectedobj = this->at( x, y, ( nb - 1 ) * dvec );
							// On vide son ancienne case
							this->set( x, y, ( nb - 1 ) * dvec, nullptr );
						}
					}
				}
			}
		} catch( out_of_range e ) {
			throw Siam::exceptions::invalid_move( "Move: out of range" ); //shielding
		}
	}

	return ejectedobj;
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

Types::Type Matrix::getType( unsigned int x, unsigned int y ) {
	Object* obj;
	try {
		obj = this->at( x, y );
		if( obj != nullptr )
			return obj->getType();
		else
			throw Siam::exceptions::invalid_object_type();
	} catch( out_of_range e ) {
		throw Siam::exceptions::invalid_move( "Get type: out of range" );
	}
}
