#ifndef HEADERS_H
# define HEADERS_H

#include "exceptions.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <fcntl.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>

#define W_TITLE "Air Hockey by Daryna Davydenko"
#define WIN_WIDTH 1401
#define WIN_HEIGHT 1001
#define TABLE_WIDTH 642
#define TABLE_HEIGHT 955
#define START_PATH "bmp/table_rules_small_new.bmp"
#define PAUSE_PATH "bmp/table_pause_small.bmp"
#define WON_PATH "bmp/fon_small_won-2.bmp"
#define LOSE_PATH "bmp/fon_small_lose-2.bmp"
#define FON_PATH "bmp/fon_small.bmp"
#define PUCK_PATH "bmp/shayba_small.bmp"
#define PUSHER_PL_PATH "bmp/clushka_red.bmp"
#define PUSHER_BOT_PATH "bmp/clushka_blue.bmp"
#define NUM_0_PATH "bmp/0_0.bmp"
#define NUM_1_PATH "bmp/1_0.bmp"
#define NUM_2_PATH "bmp/2_0.bmp"
#define NUM_3_PATH "bmp/3_0.bmp"
#define NUM_4_PATH "bmp/4_0.bmp"
#define NUM_5_PATH "bmp/5_0.bmp"
#define NUM_6_PATH "bmp/6_0.bmp"
#define BOT_SHIFT 7
#define FPS 60
#define HALF_GATE 90
#define MAX_SCORE 5
#define LEFT_WALL (window_edge_.x + (WIN_WIDTH - TABLE_WIDTH) / 2)
#define RIGHT_WALL (window_edge_.x + (WIN_WIDTH + TABLE_WIDTH) / 2)
#define TOP_WALL (window_edge_.y + (WIN_HEIGHT - TABLE_HEIGHT) / 2)
#define BOTTOM_WALL (window_edge_.y + (WIN_HEIGHT + TABLE_HEIGHT) / 2)
#define HORIZON (window_edge_.y + WIN_HEIGHT / 2)
#define TTF_FONT "ttf/HECI_CT.ttf"
#define FONT_SIZE 70

enum eDel {NoDel, TextureDel, AllDel};
enum eImage {START, FON, PAUSE_PIC, WON_PIC, LOSE_PIC, PUCK_PIC, PUSHER_PL, PUSHER_BOT, NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, TEXT};
enum eObj {PLAYER, BOT, PUCK};
enum eGame {OFF, ON, PAUSE, WON, LOSE};
enum eSound {KICK, GOAL};

struct  score
{
    int  bot;
    SDL_Rect  edge_pos_bot;
    int  player;
    SDL_Rect  edge_pos_player;
    SDL_Rect  edge_pos_text;
};

struct  vector
{
    float  x;
    float  y;
};

struct  pos_f
{
    float  x;
    float  y;
};


struct pos
{
    int  x;
    int  y;
};


#endif