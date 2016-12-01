#ifndef _FUNCTIONS_CLI_MENU_HPP_
	#define _FUNCTIONS_CLI_MENU_HPP_

	namespace Functions {
		namespace CLIs {
			class Menu {
				private:
					std::string m_header;
					std::vector<std::string> m_choices;

				public:
					Menu( std::string header, std::vector<std::string> choices, unsigned char back_color, unsigned char header_color, unsigned char selection_color );
					void setOffsets( int& offset_x, int& offset_y );
					unsigned int getChoice() const;
			};
		}
	}
#endif
