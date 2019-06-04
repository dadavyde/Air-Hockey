#include "Bot.hpp"

Bot::Bot() : Object()
{
    edge_pos_ = (SDL_Rect){700, 100, 0, 0};
}

void Bot::find_origin()
{
    if (origin_f_.x < LEFT_WALL + radius_)
        origin_f_.x = LEFT_WALL + radius_;
    else if (origin_f_.x > RIGHT_WALL - radius_)
        origin_f_.x = RIGHT_WALL - radius_;

    if (origin_f_.y > HORIZON - radius_)
        origin_f_.y = HORIZON - radius_;
    else if (origin_f_.y < TOP_WALL + radius_)
        origin_f_.y = TOP_WALL + radius_;
}

void  Bot::find_direction(Object *player, Object *puck)
{
    (void)player;

    if (puck->get_origin_f().x > origin_f_.x &&
        (puck->get_origin_f().x - window_edge_.x - puck->get_radius() - (WIN_WIDTH - TABLE_WIDTH) / 2 > 0))
        origin_f_.x += 1;
    else
        origin_f_.x -= 1;
    old_origin_f_ = origin_f_;
    find_origin();
    if (puck->get_origin_f().y > origin_f_.y)
        origin_f_.y += 5;
    else
        origin_f_.y -= 5;
    direct.x = (origin_f_.x - old_origin_f_.x) * FPS;
    direct.y = (origin_f_.y - old_origin_f_.y) * FPS;
}
