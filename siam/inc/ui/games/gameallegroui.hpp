#ifndef _ECE_SIAM_UI_GAMES_ALLEGRO_HPP_
	#define _ECE_SIAM_UI_GAMES_ALLEGRO_HPP_

	#include <allegro.h>
	#include "../../../../winhack.h"
	#include <jpgalleg.h>
	#include <loadpng.h>
	#include <fblend.h>
	#include <vector>
	#include <ios>
	#include "../../../../allegro/popup.hpp"
	#include "../../../../allegro/circularmenu.hpp"
	#include "../gameui.hpp"
	#include "../audio/FMOD.hpp"

	#define ACTION_MENU_RADIUS_PADDING 5
	#define ACTION_MENU_SIZE 42
	#define PLAYER_NAME_PADDING_W 10
	#define PLAYER_NAME_PADDING_H 2
	#define ACTION_PANE_COLOR makecol( 200, 200, 200 )
	#define ACTION_PANE_PADDING 10
	#define COLOR_ACTIVE_PLAYER makecol( 27, 144, 170 )
	#define COLOR_INACTIVE_PLAYER makecol( 3, 21, 25 )
	#define COLOR_PLAYER_RHINOCEROS makecol( 3, 21, 25 )
	#define COLOR_PLAYER_ELEPHANT makecol( 27, 144, 170 )
	#define COLOR_SELECTION makecol( 255, 0, 0 )
	#define COLOR_DIRECTION_SELECTION makecol( 255, 255, 0 )
	#define COLOR_SELECTION_BLENDFACTOR 80
	#define VICTORY_PADDING 50

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

						Siam::Matrixs::Direction getDirection() const;
						void setDirection( Siam::Matrixs::Direction direction );

						Siam::Objects::Types::Type getType() const;

				};

				class Allegro : public Siam::UI::Game {
					private:
						std::unordered_map<const Siam::Object*, AllegroObject> m_objects;
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						BITMAP* m_page;
						FONT* m_textFont;
						Functions::Allegro::CircularMenu* m_actionsMenu;
						bool mouseL = false;
						bool prevMouseL = false;
						bool keyEsc = false;
						bool prevKeyEsc = false;
						Siam::Players::Action m_selectedAction = Siam::Players::Action::Nothing;

						void loadSprites();
						void loadFonts();
						void loadMenus();
						void loadBackgrounds();

						void display( bool update = true );
						void displayMatrix();
						void displayPlayers();
						void displayCurrentAction();
						void highlightSelectedPiece( unsigned int x, unsigned int y, int color = COLOR_SELECTION );

						void updateInputs();

						BITMAP* getAnimalSprite( Siam::Objects::Types::Type animal ) const;

					public:
						Allegro( const std::vector<std::vector<Siam::Object*>>& board, const std::vector<Siam::Player>& players, std::vector<Siam::Player>::iterator& currentPlayer, Siam::UI::Audio::FMOD& fmod );
						~Allegro();

						void showError( std::string msg );
						void getPlayerCoords( unsigned int& x, unsigned int& y, Siam::Matrixs::Direction* dir );
						void addPiece( const Object* obj, unsigned int x, unsigned int y );
						void removePiece( const Object* obj );
						void movePiece( std::map<const Siam::Object*, std::pair<unsigned int, unsigned int>>& movements );
						void orientPiece( const Object* obj );
						void ejectPiece( const Object* obj );
						void playerTurnBegin( Siam::Player& player );
						void playerTurnEnd( Siam::Player& player );
						Players::Action getPlayerAction( Siam::Player& player );
						void victory( Siam::Player& player );

						void setSelectedAction( Siam::Players::Action action );
						void showPause();
				};
			}
		}
	}
#endif
