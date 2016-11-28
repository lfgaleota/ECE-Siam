#ifndef _ECE_SIAM_GAME_HPP_
	#define _ECE_SIAM_GAME_HPP_

	#include <iostream>
	#include <vector>
	#include "matrix.hpp"
	#include "object.hpp"
	#include "player.hpp"

	namespace Siam {
		class Game {
			private:
				Siam::Matrix m_board;
				std::vector<Siam::Player> m_players;
				std::vector<Siam::Player>::iterator m_currentPlayer;
				void display();
				void addOnBoard();
				void removeFromBoard();
				void moveOnBoard();
				void orientOnBoard();
				void playerTurn();
				bool isFinished();
				void victory();

			public:
				Game( std::vector<Siam::Player> players );
		};
	}


#endif //_ECE_SIAM_GAME_HPP_
