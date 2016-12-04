#ifndef _ECE_SIAM_GAME_HPP_
	#define _ECE_SIAM_GAME_HPP_

	#include <vector>
	#include "matrix.hpp"
	#include "object.hpp"
	#include "player.hpp"
	#include "ui/gameui.hpp"

	namespace Siam { //in the namespace Siam
		class Game { //create a game class
			private: //contains
				Siam::Matrix m_board; //a board
				std::vector<Siam::Player> m_players; //players
				std::vector<Siam::Player>::iterator m_currentPlayer; //an iterator of players (we need to know who's turn it is)
				Siam::UI::Game* m_ui;
				bool won = false;

				void addOnBoard(); //add a piece to the board
				void removeFromBoard(); //remove a piece from the board
				void moveOnBoard(); //make a move
				void orientOnBoard(); //reorient a piece on the board
				void playerTurn(); //a turn
				void victory(); //victory !

			public:
				Game( std::vector<Siam::Player> players, Siam::UI::Audio::FMOD& fmod, bool allegro = false ); //game method
		};
	}



#endif //_ECE_SIAM_GAME_HPP_
