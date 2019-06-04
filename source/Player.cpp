#include "Player.hpp"

Player::Player() : Object()
{
    edge_pos_ = (SDL_Rect){700, 900, 0, 0};
}

void Player::find_origin()//global position
{
    if (origin_f_.x < LEFT_WALL + radius_)
        origin_f_.x = LEFT_WALL + radius_;
    else if (origin_f_.x > RIGHT_WALL - radius_)
        origin_f_.x = RIGHT_WALL - radius_;

    if (origin_f_.y < HORIZON + radius_)
        origin_f_.y = HORIZON + radius_;
    else if (origin_f_.y > BOTTOM_WALL - radius_)
        origin_f_.y = BOTTOM_WALL - radius_;
}

void 	Player::find_direction(Object *player, Object *bot)
{
    (void)player;
    (void)bot;
    direct.x = (origin_f_.x - old_origin_f_.x) * FPS;
    direct.y = (origin_f_.y - old_origin_f_.y) * FPS;

}