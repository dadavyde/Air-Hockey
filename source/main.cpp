#include <iostream>
#include <Game.hpp>
#include "exceptions.hpp"

int main()
{
	Game  game;

	try {
		game.set_textures();
	}
	catch (SdlErr &e) {
		std::cout << SDL_GetError() << END_RED << std::endl;//TODO check
		return (-1);
	}
	try {
		game.run();//TODO можно ли в один трай запихнуть
	}
	catch (SdlErr &e) {
		std::cout << e.what() << SDL_GetError() << END_RED << std::endl;
		return (-1);
	}
}
