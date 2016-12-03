#ifndef _ECE_SIAM_UI_GAMES_ALLEGRO_HPP_
	#define _ECE_SIAM_UI_GAMES_ALLEGRO_HPP_

	#include <allegro.h>
	#include "../../../../winhack.h"
	#include <jpgalleg.h>
	#include <loadpng.h>
	#include <vector>
	#include <ios>
	#include "../../../../allegro/popup.hpp"
	#include "../gameui.hpp"
	#include "../audio/FMOD.hpp"

	namespace Siam {
		namespace UI {
			namespace Games {
				class AllegroObject {
					private:
						unsigned int m_x;
						unsigned int m_y;
						Siam::Objects::Types::Type m_type;
						Siam::Matrixs::Direction m_direction;

					public:
						AllegroObject();
						AllegroObject( unsigned int x, unsigned int y, Siam::Objects::Types::Type type, Siam::Matrixs::Direction direction );

						unsigned int getX() const;
						void setX( unsigned int x );

						unsigned int getY() const;
						void setY( unsigned int y );

						Matrixs::Direction getDirection() const;
						void setDirection( Matrixs::Direction direction );

				};

				class Allegro : public Siam::UI::Game {
					private:
						std::unordered_map<const Siam::Object*, AllegroObject> m_objects;
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						Siam::UI::Audio::FMOD fmod;
						BITMAP* page;

						void loadSprites();

						void display();

					public:
						Allegro( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer );
						~Allegro();

						void showError( std::string msg );
						void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir );
						void addPiece( const Object*, unsigned int x, unsigned int y );
						void removePiece( const Object* );
						void movePiece( std::map<const Siam::Object*, std::pair<unsigned int, unsigned int>>& movements );
						void orientPiece( const Object* );
						void playerTurnBegin( Siam::Player& player );
						void playerTurnEnd( Siam::Player& player );
						Players::Action getPlayerAction( Siam::Player& player );
						void victory( Siam::Player& player );
				};
			}
		}
	}
#endif
