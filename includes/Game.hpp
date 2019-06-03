/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:06:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/05/28 20:06:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef AIRHOCKEY_GAME_HPP
#define AIRHOCKEY_GAME_HPP

#include "headers.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "Puck.hpp"

using namespace std::chrono;


class Game
{
public:
	Game();
	~Game();
	Game &operator=(const Game &other);
	Game(const Game &other);

	void  run();
	void  init();
	void  set_textures();
	void  draw_scene();
	void  handle_events();
	//void  play_music();
	void  key_down(int &running);
	void  update_image();

private:
	SDL_Window		*window_;
	std::vector<std::string>	textures_name = {START_PATH, PAUSE_PATH, FON_PATH, PUCK_PATH, PUSHER_PATH, WON_PATH, LOSE_PATH,
												 NUM_0_PATH, NUM_1_PATH, NUM_2_PATH, NUM_3_PATH, NUM_4_PATH, NUM_5_PATH, NUM_6_PATH};
	std::vector<SDL_Surface*>	textures_;
	SDL_Surface		*screen_;
	SDL_Event		event_;
	Mix_Music		*music_;
	eDel 			del_flag_;
	pos				mouse_;
	pos				window_edge_;
	std::vector<Object*>	objects;
	eGame 			game_status_;
	score			score_;
	milliseconds 	ms;
	bool			player_turn_;
};


#endif
