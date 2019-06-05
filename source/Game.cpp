#include "Game.hpp"

Game::Game() : window_(), screen_(), event_(), music_(), del_flag_(NoDel), mouse_(), window_edge_(), game_status_(OFF), player_turn_(true)
{
    score_ = (score){0, (SDL_Rect){150, 180, 0, 0}, 0, (SDL_Rect){1180, 820, 0, 0}, (SDL_Rect){620, 200, 0, 0}};
    ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    try {
        set_textures();
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
    if (TTF_Init() != 0)
        throw SdlErr();
    window_ = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_ == nullptr)
        throw SdlErr("SDL_CreateWindow Error: ");
    screen_ = SDL_GetWindowSurface(window_);
    SDL_GetWindowPosition(window_, &window_edge_.x, &window_edge_.y);
    del_flag_ = AllDel;
    SDL_BlitSurface(textures_[START], nullptr, screen_, nullptr);
    SDL_UpdateWindowSurface(window_);
    try {
        init();
        handle_events();
    }
    catch (SdlErr &e) {
        throw (e);
    }
}

void Game::init()
{
    font = TTF_OpenFont(TTF_FONT, FONT_SIZE);
    if (font == nullptr)
        throw SdlErr("TTF_OpenFont() Failed: ");
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
    for (int status = PAUSE; status <= LOSE; status++)
        if (game_status_ == status)
        {
            SDL_BlitSurface(textures_[status], nullptr, screen_, nullptr);//PAUSE_PIC, WON_PIC, LOSE_PIC
            if (status > PAUSE)
                SDL_BlitSurface(textures_[TEXT], nullptr, screen_, &score_.edge_pos_text);
        }
    if (game_status_ <= ON)
    {
        set_objects_position();
        if (score_.bot > MAX_SCORE || score_.player > MAX_SCORE) {
            Mix_PauseMusic();//Pause the music
            if (score_.bot > MAX_SCORE)
                game_status_ = LOSE;
            else
                game_status_ = WON;
            std::string text = std::to_string(score_.bot) + " - " + std::to_string(score_.player);
            textures_.push_back(TTF_RenderText_Solid(font, text.c_str(), (SDL_Color){0, 0, 0, 0}));
        }
        if (objects[PUCK]->is_goal())//шайба в воротах
        {
            if (objects[PUCK]->get_origin_f().y < window_edge_.y + WIN_HEIGHT / 2) {
                player_turn_ = false;
                score_.player++;
            }
            else {
                player_turn_ = true;
                score_.bot++;
            }
            SDL_Delay(700);
            player_turn_ ? objects[PUCK]->set_origin_f(1100, 800) : objects[PUCK]->set_origin_f(1400, 600);
            player_turn_ ? reset_puck_position(PLAYER) : reset_puck_position(BOT);
            objects[PUCK]->set_direction(0, 0);
        }
        put_sufaces();
    }
}

void  Game::set_objects_position()
{
    objects[PLAYER]->set_origin_f(mouse_.x, mouse_.y);
    objects[PLAYER]->find_direction(objects[PLAYER], objects[BOT]);
    objects[PLAYER]->set_edge_pos();
    objects[BOT]->set_edge_pos();
    objects[BOT]->find_direction(objects[PLAYER], objects[PUCK]);
    objects[PUCK]->find_direction(objects[PLAYER], objects[BOT]);
    objects[PUCK]->set_edge_pos();
}

void Game::put_sufaces()
{
    SDL_BlitSurface(textures_[FON], nullptr, screen_, nullptr);
    SDL_BlitSurface(textures_[PUSHER_PL], nullptr, screen_, objects[PLAYER]->get_edge_pos());
    SDL_BlitSurface(textures_[PUSHER_BOT], nullptr, screen_, objects[BOT]->get_edge_pos());
    SDL_BlitSurface(textures_[PUCK_PIC], nullptr, screen_, objects[PUCK]->get_edge_pos());
    SDL_BlitSurface(textures_[NUM_0 + score_.bot], nullptr, screen_, &score_.edge_pos_bot);
    SDL_BlitSurface(textures_[NUM_0 + score_.player], nullptr, screen_, &score_.edge_pos_player);
}

void  Game::handle_events()
{
    int     running;

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
            SDL_Delay(30 - ms.count());
    }
}


void  Game::key_down(int &running)
{
    if (event_.type == SDL_QUIT || event_.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        running = false;
    else if (event_.key.keysym.sym == SDLK_SPACE)
    {
        if (game_status_ == ON) {
            game_status_ = PAUSE;
            Mix_PauseMusic();//Pause the music
        }
        else {
            game_status_ = ON;
            Mix_ResumeMusic();//Resume the music
        }
    }
    else if ((event_.key.keysym.sym == SDLK_KP_ENTER || event_.key.keysym.sym == SDLK_RETURN) &&
            (game_status_ == OFF || game_status_ >= WON))//start the game
    {
        if (game_status_ >= WON) {
            Mix_ResumeMusic();
            reset_game();
        }
        game_status_ = ON;
        SDL_WarpMouseInWindow(window_, 800, 800);//установить курсор мышки в позицию
    }
}

void  Game::update_image()
{
    if (game_status_ != OFF) {
        draw_scene();
        SDL_UpdateWindowSurface(window_);
    }
}

void    Game::reset_puck_position(eObj name)
{
    objects[PUCK]->set_origin_f(1100, 800);
    if (objects[PUCK]->get_origin_f().x > objects[name]->get_origin_f().x &&
        objects[PUCK]->get_origin_f().x - objects[PUCK]->get_radius() - objects[name]->get_origin_f().x - objects[name]->get_radius() < 5)
        objects[PUCK]->set_origin_f(1105 + objects[PUCK]->get_radius() + objects[name]->get_radius(), 800);
    else if (objects[PUCK]->get_origin_f().x < objects[name]->get_origin_f().x &&
             objects[name]->get_origin_f().x - objects[name]->get_radius() - objects[PUCK]->get_origin_f().x - objects[PUCK]->get_radius() < 5)
        objects[PUCK]->set_origin_f(1095 - objects[PUCK]->get_radius() - objects[name]->get_radius(), 800);
    if (objects[PUCK]->get_origin_f().y > objects[name]->get_origin_f().y &&
        objects[PUCK]->get_origin_f().y - objects[PUCK]->get_radius() - objects[name]->get_origin_f().y - objects[name]->get_radius() < 5)
        objects[PUCK]->set_origin_f(-1, 805 + objects[PUCK]->get_radius() + objects[name]->get_radius());
    else if (objects[PUCK]->get_origin_f().y < objects[name]->get_origin_f().y &&
             objects[name]->get_origin_f().y - objects[name]->get_radius() - objects[PUCK]->get_origin_f().y - objects[PUCK]->get_radius() < 5)
        objects[PUCK]->set_origin_f(-1, 795 - objects[PUCK]->get_radius() - objects[name]->get_radius());
}

void Game::reset_game()
{
    SDL_FreeSurface(textures_[TEXT]);
    textures_.pop_back();
    objects[BOT]->set_origin_f(1100, 500);
    objects[BOT]->set_old_origin_f(objects[BOT]->get_origin_f());
    objects[PLAYER]->set_origin_f(mouse_.x, mouse_.y);
    objects[PLAYER]->set_old_origin_f(objects[PLAYER]->get_origin_f());
    score_.player = 0;
    score_.bot = 0;
}
