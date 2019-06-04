#include "Game.hpp"

Game::Game() : window_(), screen_(), event_(), music_(), del_flag_(NoDel), game_status_(OFF), player_turn_(true)
{
	mouse_ = (pos){0, 0};
	window_edge_ = (pos){0, 0};
	score_ = (score){0, (SDL_Rect){150, 180, 0, 0}, 0, (SDL_Rect){1180, 820, 0, 0}};
	ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
	try {
		set_textures();
		//TODO check
	}
	catch (SdlErr &e) {
		throw SdlErr(e);
	}
}

Game::~Game()
{
	if (del_flag_ > NoDel)
		for (auto & texture : textures_)
			SDL_FreeSurface(texture);
	if (del_flag_ == AllDel)
	{
		SDL_DestroyWindow(window_);
		SDL_Quit();
	}
}

Game& Game::operator=(const Game &other)
{
	if (this != &other)
	{
		this->window_ = other.window_;
		this->textures_ = other.textures_;
		this->screen_ = other.screen_;
		this->music_ = other.music_;
	}
	return *this;
}

Game::Game(const Game &other)
{
	*this = other;
}

void  Game::set_textures()
{
	SDL_Surface  *tmp;

	for (auto & name : textures_name){
		tmp = SDL_LoadBMP(name.c_str());
		if (tmp == nullptr)
			throw SdlErr(name);
		name.insert(0, "Unable to load image ");
		name += ", ";
		SDL_SetColorKey(tmp, true, 0xFFFFFF);
		textures_.push_back(SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0));
		SDL_FreeSurface(tmp);
	}
	del_flag_ = TextureDel;
}

void Game::run()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw SdlInitErr();
	window_ = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);//SDL_WINDOW_ALLOW_HIGHDPI
	if (window_ == nullptr)
		throw SdlErr("SDL_CreateWindow Error: ");
	screen_ = SDL_GetWindowSurface(window_);
	SDL_GetWindowPosition(window_, &window_edge_.x, &window_edge_.y);
	del_flag_ = AllDel;
	SDL_BlitSurface(textures_[START], nullptr, screen_, nullptr);
	SDL_UpdateWindowSurface(window_);
	init();
	try
	{
		handle_events();
	}
	catch (SdlErr &e) {
		throw (e);
	}
}

void Game::init()
{
	objects.push_back(new Player());
	objects.push_back(new Bot());
	objects.push_back(new Puck());
	for (auto object : objects)
	{
		object->set_direction(0, 0);
		object->set_win_edge_pos(window_edge_);
	}
	SDL_GetGlobalMouseState(&mouse_.x, &mouse_.y);
	objects[PLAYER]->set_sizes(textures_[PUSHER_PL]->h, textures_[PUSHER_PL]->w);
	objects[BOT]->set_sizes(textures_[PUSHER_BOT]->h, textures_[PUSHER_BOT]->w);
	objects[PUCK]->set_sizes(textures_[PUCK_PIC]->h, textures_[PUCK_PIC]->w);
	try {
		music_.play_music();
	}
	catch (SdlErr &e) {
		throw (e);
	}
	objects[PUCK]->set_music(music_);
}

void  Game::draw_scene()
{
	if (game_status_ == PAUSE)
		SDL_BlitSurface(textures_[PAUSE_PIC], nullptr, screen_, nullptr);
	else if (game_status_ == WON)
		SDL_BlitSurface(textures_[WON_PIC], nullptr, screen_, nullptr);
	else if (game_status_ == LOSE)
		SDL_BlitSurface(textures_[LOSE_PIC], nullptr, screen_, nullptr);
	else
	{
		if (objects[PUCK]->get_origin_f().x < 5)//шайба в воротах
		{
			if (objects[PUCK]->get_origin_f().y < window_edge_.y + WIN_HEIGHT / 2)
			{
				player_turn_ = false;
				score_.player++;
			}
			else
			{
				player_turn_ = true;
				score_.bot++;
			}
			SDL_Delay(700);
			player_turn_ ? objects[PUCK]->set_origin_f(1100, 800) : objects[PUCK]->set_origin_f(1400, 600);
			//TODO сделать чтобы не накладывались
			objects[PUCK]->set_direction(0, 0);
		}
		else
		{
			objects[PUCK]->find_direction(objects[PLAYER], objects[BOT]);
			objects[PUCK]->set_edge_pos();
		}
		objects[PLAYER]->set_origin(mouse_);
		objects[PLAYER]->set_edge_pos();
		objects[PLAYER]->find_direction(objects[PLAYER], objects[BOT]);
		objects[PLAYER]->set_edge_pos();
		objects[BOT]->set_edge_pos();
		objects[BOT]->find_direction(objects[PLAYER], objects[PUCK]);

		SDL_BlitSurface(textures_[FON], nullptr, screen_, nullptr);
		SDL_BlitSurface(textures_[PUSHER_PL], nullptr, screen_, objects[PLAYER]->get_edge_pos());
		SDL_BlitSurface(textures_[PUSHER_BOT], nullptr, screen_, objects[BOT]->get_edge_pos());
		SDL_BlitSurface(textures_[PUCK_PIC], nullptr, screen_, objects[PUCK]->get_edge_pos());
		SDL_BlitSurface(textures_[NUM_0 + score_.bot], nullptr, screen_, &score_.edge_pos_bot);
		SDL_BlitSurface(textures_[NUM_0 + score_.player], nullptr, screen_, &score_.edge_pos_player);

		if (score_.bot > MAX_SCORE)
			game_status_ = LOSE;
		else if (score_.player > MAX_SCORE)
			game_status_ = WON;
	}
}

void  Game::handle_events()
{
	int			running;

	running = true;
	while (running)
	{
		(SDL_PollEvent(&event_));
		ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		if (event_.type == SDL_KEYDOWN)
			key_down(running);
		if (event_.type == SDL_MOUSEMOTION)
			SDL_GetGlobalMouseState(&mouse_.x, &mouse_.y);
		update_image();
		ms = (duration_cast< milliseconds >(system_clock::now().time_since_epoch()) - ms);
		if (ms.count() < 30 && ms.count() > 0)
			SDL_Delay(30 - ms.count());//TODO check
	}
}


void  Game::key_down(int &running)
{
	if (event_.type == SDL_QUIT || event_.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		running = false;
	else if (event_.key.keysym.sym == SDLK_SPACE)
	{
		if (game_status_ == ON)
			game_status_ = PAUSE;
		else
			game_status_ = ON;
	}
	else if ((event_.key.keysym.sym == SDLK_KP_ENTER || event_.key.keysym.sym == SDLK_RETURN) && game_status_ == OFF)//TODO начать игру
	{
		game_status_ = ON;
		SDL_WarpMouseInWindow(window_, 800, 800);
	}
}

void  Game::update_image()
{
	if (game_status_ != OFF)
	{
		draw_scene();
		SDL_UpdateWindowSurface(window_);
	}
}

