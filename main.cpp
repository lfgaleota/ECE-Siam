#include <iostream>
#include <vector>
#include "siam/inc/matrix.hpp"
#include "siam/inc/objects/entity.hpp"
#include "siam/inc/objects/rhinoceros.hpp"
#include "siam/inc/objects/elephant.hpp"

using namespace std;

void display( Siam::Matrix& board ) {
	auto& matrix = board.getBoard();
	Siam::Object* elem = nullptr;

	for( unsigned int j = 0; j < matrix.size(); j++ ) {
		for( unsigned int i = 0; i < matrix[ j ].size(); i++ ) {
			elem = matrix[ i ][ j ];

			if( elem != nullptr ) {
				switch( elem->getType() ) {
					case Siam::Objects::Types::Type::Mountain:
						std::cout << "M";
						break;
					case Siam::Objects::Types::Type::Rhinoceros:
						std::cout << "R";
						break;
					case Siam::Objects::Types::Type::Elephant:
						std::cout << "E";
						break;
					case Siam::Objects::Types::Type::Object:
						break;
					case Siam::Objects::Types::Type::Entity:
						break;
				}
				switch( elem->getDirection() ) {
					case Siam::Matrixs::Direction::Left:
						std::cout << "<";
						break;
					case Siam::Matrixs::Direction::Right:
						std::cout << ">";
						break;
					case Siam::Matrixs::Direction::Top:
						std::cout << "/";
						break;
					case Siam::Matrixs::Direction::Bottom:
						std::cout << "\\";
						break;
				}
			} else {
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

void playerchoice( Siam::Player* player1, Siam::Player* player2 ) {
	bool choix;
	std::string name;

	cout << "joueur 1 entrez votre nom : ";
	cin >> name;
	player1->setname( name );
	cout << "joueur 2 entrez votre nom : ";
	cin >> name;
	player2->setname( name );

	cout << "vous etes plutot du genre a jouer les elephants " << player1->getname() << " non ?" << endl;
	cout << "0:OUI 1:NON" << endl;
	cin >> choix;

	player1->savechoice( choix );
	player2->savechoice( !choix );

	cout << player1->getname() << " jouera les " << player1->getanimalchosen() << endl;
	cout << player2->getname() << " jouera les " << player2->getanimalchosen() << endl;


}

void ajout( Siam::Player* player1, Siam::Player* player2, Siam::Matrix& board ) {
	unsigned int x, y;
	char direction;

	cout << "A quelles coordonnees ?" << endl;
	cin >> x;
	cin >> y;
	cout << "Dans quelle direction ?(h/b/g/d)" << endl;
	cin >> direction;

	switch( direction ) {

		case 'g' :

			if( player1->getanimalchosen() == "Elephant" ) {
				board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Left, nullptr ), x, y );
			} else
				board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Left, nullptr ), x, y );
			break;

		case 'd' :


			if( player1->getanimalchosen() == "Elephant" ) {
				board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Right, nullptr ), x, y );
			} else
				board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Right, nullptr ), x, y );
			break;

		case 'h' :


			if( player1->getanimalchosen() == "Elephant" && x <= 4 && x >= 0 && y <= 4 && y >= 0 ) {
				board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Top, nullptr ), x, y );
			} else
				board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Top, nullptr ), x, y );
			break;

		case 'b' :


			if( player1->getanimalchosen() == "Elephant" && x <= 4 && x >= 0 && y <= 4 && y >= 0 ) {
				board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Bottom, nullptr ), x, y );
			} else
				board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Bottom, nullptr ), x, y );
			break;


		default :

			cout << "error" << endl;

			break;

	}


}

void remove( Siam::Matrix& board ) {
	unsigned int x, y;
	cout << "A quelles coordonnees ?" << endl;
	cin >> x;
	cin >> y;

	board.remove( x, y );

}

void tour( Siam::Player* player1, Siam::Player* player2, Siam::Matrix& board ) {

	int choix;

	if( board.gettour() % 2 == 0 )
		cout << "c'est au tour de " << player1->getname() << endl;
	else
		cout << "c'est au tour de " << player2->getname() << endl;

	cout << "vos possibilites sont : " << endl;
	cout << "   1. Ajouter une nouvelle piece sur le terrain" << endl;
	cout << "   2. Enlever une piece du terrain" << endl;
	cout << "   3. Bouger une piece sur le terrain" << endl;
	cout << "   4. Changer l'orientation d'une piece" << endl;
	cout << endl;
	cout << "quel est votre choix ?";
	cin >> choix;

	switch( choix ) {
		case 1 :
			//add
			ajout( player1, player2, board );
			break;
		case 2 :
			//remove
			remove( board );
			break;
		case 3 :
			//move
			break;
		case 4 :
			//orient
			break;
	}

	board.settour();
}

int main() {
	unsigned int x = 0, y = 0;

	Siam::Player player1( "Louis-Félix" ), player2( "Romain" );

	playerchoice( & player1, & player2 );

	Siam::Matrix board(); //on initialise le terrain de jeu !

	//board.add( new Siam::Objects::Elephant( "E1", 1, Siam::Matrixs::Direction::Left, nullptr ), x, y );
	//board.add( new Siam::Objects::Rhinoceros( "R1", 1, Siam::Matrixs::Direction::Right, nullptr ), x + 1, y ); //test d'entrée dans la matrice d'une entité
	//board.add( new Siam::Objects::Rhinoceros( "R2", 1, Siam::Matrixs::Direction::Right, nullptr ), x + 2, y );
	//board.add( new Siam::Objects::Elephant( "E2", 1, Siam::Matrixs::Direction::Left, nullptr ), x + 3, y );

	//display( board );

	//std::cout << board.getForce( 1, 0, board.getDirectionVector( Siam::Matrixs::Direction::Right ) ) << std::endl;

	//board.remove( x, y ); //on enlève une pièce qui est au bord

	tour( & player1, & player2, board );
	tour( & player1, & player2, board );
	return 0;
}
