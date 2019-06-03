/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 20:41:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/06/01 20:41:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

#include "exceptions.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include <fcntl.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>

#define W_TITLE "Air Hockey by Daryna Davydenko"
#define WIN_WIDTH 1401
#define WIN_HEIGHT 1001
#define TABLE_WIDTH 670
#define TABLE_HEIGHT 1020
#define START_PATH "bmp/table_rules_small_new_6.bmp"
#define PAUSE_PATH "bmp/table_pause_small.bmp"
#define WON_PATH "bmp/fon_small_won.bmp"
#define LOSE_PATH "bmp/fon_small_lose.bmp"
#define FON_PATH "bmp/fon_small.bmp"
#define PUCK_PATH "bmp/shayba_small.bmp"
#define PUSHER_PATH "bmp/clushka_small.bmp"
#define KICK_SOUND_PATH "sounds/Kick.wav"
#define MUSIC_PATH "bmp/sounds/music1.wav"
#define NUM_0_PATH "bmp/0_0.bmp"
#define NUM_1_PATH "bmp/1_0.bmp"
#define NUM_2_PATH "bmp/2_0.bmp"
#define NUM_3_PATH "bmp/3_0.bmp"
#define NUM_4_PATH "bmp/4_0.bmp"
#define NUM_5_PATH "bmp/5_0.bmp"
#define NUM_6_PATH "bmp/6_0.bmp"
#define PLAYER_SHIFT 20
#define PLAYER_SHIFT2 53
#define FPS 25
#define HALF_GATE 90
#define MAX_SCORE 6

enum eDel {NoDel, TextureDel, AllDel};
enum eImage {START, PAUSE_PIC, FON, PUCK_PIC, PUSHER, WON_PIC, LOSE_PIC, NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6};
enum eObj {PLAYER, BOT, PUCK};
enum eGame {OFF, ON, PAUSE, WON, LOSE};

struct  score
{
	int  bot;
	SDL_Rect  edge_pos_bot;
	int  player;
	SDL_Rect  edge_pos_player;
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