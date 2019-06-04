#include <iostream>
#include <Game.hpp>
#include "exceptions.hpp"

int main()
{
	Game  *game;

	try {
		game = new Game();
	}
	catch (SdlErr &e) {
		std::cout << START_RED << "SDL error: " << SDL_GetError() << END_RED << std::endl;//TODO check
		return (1);
	}
	game->run();
	delete game;
}
