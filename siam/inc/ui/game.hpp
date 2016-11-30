#ifndef _ECE_SIAM_UI_GAME_HPP_
	#define _ECE_SIAM_UI_GAME_HPP_

	#include "../matrix.hpp"
	#include "../object.hpp"
	#include "../objects/types/type.hpp"
	#include "../player.hpp"
	#include "../../../cli/cli.hpp"

	namespace Siam {
		namespace UI {
			class Game {
				protected:
					const std::vector<std::vector<Siam::Object*>>& m_board;
					const std::vector<Siam::Player>& m_players;

				public:
					Game( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players ) : m_board( board ), m_players( players ) {};
					virtual ~Game() {};
					virtual void showError( std::string msg ) = 0;
					virtual void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir )= 0;
					virtual void addPiece( const Object* ) = 0;
					virtual void removePiece( const Object* ) = 0;
					virtual void movePiece( std::map<const Siam::Object*, std::pair<unsigned int, unsigned int>>& movements ) = 0;
					virtual void orientPiece( const Object*, Siam::Matrixs::Direction oldDir ) = 0;
					virtual void playerTurnBegin( Siam::Player& player ) = 0;
					virtual void playerTurnEnd( Siam::Player& player ) = 0;
					virtual Players::Action getPlayerAction( Siam::Player& player ) = 0;
					virtual void victory( Siam::Player& player ) = 0;
			};
		}
	}
#endif //_ECE_SIAM_UI_GAME_HPP_
