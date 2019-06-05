#include "Game.hpp"

int main()
{
    Game  *game;

    try {
        game = new Game();
        game->run();
    }
    catch (SdlErr &e) {
        std::cout << START_RED << "SDL error: " << SDL_GetError() << END_RED << std::endl;
        return (1);
    }
    delete game;
}
