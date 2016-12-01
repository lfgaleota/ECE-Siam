#ifndef _ECE_SIAM_UI_GAME_CLI_HPP_
	#define _ECE_SIAM_UI_GAME_CLI_HPP_

	#include <iostream>
	#include "../../matrix.hpp"
	#include "../../object.hpp"
	#include "../../objects/types/type.hpp"
	#include "../../player.hpp"
	#include "../game.hpp"
	#include "../../../../cli/cli.hpp"
	#include <fstream>
	#include <sstream>

	namespace Siam {
		namespace UI {
			namespace Games {
				class CLI : public Siam::UI::Game {
					private:
						Functions::CLI cli;
						void display();
						void displayMatrix();
						void displayPlayers();
						void displayActions();
						std::vector<std::string> m_displayMatrix;
						void loadDisplayMatrix();

					public:
						CLI( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer );
						void showError( std::string msg );
						void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir );
						void addPiece( const Object* );
						void removePiece( const Object* );
						void movePiece( std::map<const Siam::Object*, std::pair<unsigned int, unsigned int>>& movements );
						void orientPiece( const Object*, Siam::Matrixs::Direction oldDir );
						void playerTurnBegin( Siam::Player& player );
						void playerTurnEnd( Siam::Player& player );
						Players::Action getPlayerAction( Siam::Player& player );
						void victory( Siam::Player& player );
				};
			}
		}
	}
#endif //_ECE_SIAM_UI_GAME_CLI_HPP_
