#ifndef AIRHOCKEY_GAME_HPP
#define AIRHOCKEY_GAME_HPP

#include "headers.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "Puck.hpp"
#include "Music.hpp"

using namespace std::chrono;


class Game
{
public:
    Game();
    ~Game();
    Game &operator=(const Game &other);
    Game(const Game &other);

    void  set_textures();
    void  run();
    void  init();
    void  draw_scene();
    void  set_objects_position();
    void  put_sufaces();
    void  handle_events();
    void  key_down(int &running);
    void  update_image();
    void  reset_puck_position(eObj name);
    void  reset_game();

private:
    SDL_Window                  *window_;
    std::vector<std::string>    textures_name = {START_PATH, FON_PATH, PAUSE_PATH, WON_PATH, LOSE_PATH, PUCK_PATH, PUSHER_PL_PATH, PUSHER_BOT_PATH,
                                                 NUM_0_PATH, NUM_1_PATH, NUM_2_PATH, NUM_3_PATH, NUM_4_PATH, NUM_5_PATH, NUM_6_PATH};
    std::vector<SDL_Surface*>   textures_;
    SDL_Surface                 *screen_;
    SDL_Event                   event_;
    Music                       music_;
    eDel                        del_flag_;
    pos                         mouse_;
    pos                         window_edge_;
    std::vector<Object*>        objects;
    eGame                       game_status_;
    score                       score_;
    milliseconds                ms;
    bool                        player_turn_;
    TTF_Font                    *font;
};


#endif
