#include <iostream>
#include "cli.hpp"

int main() {
	CLI cli = CLI();
	cli.setColor( BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN |
	              FOREGROUND_INTENSITY );
	std::cout << "BONFDBFVJGSHKDSGDFGKHD" << std::endl;
	cli.pause();
	cli.setColor( BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY );
	cli.clearScreen();
	cli.resetColor();
	cli.moveCursor( 5, 5 );
	std::cout << "Sans couleurs!" << std::endl;
	cli.pause();
	return 0;
}
