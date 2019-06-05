#include "Puck.hpp"

Puck::Puck() : Object()
{
    origin_f_ = (pos_f){1100, 800};
}

void Puck::find_origin()
{
    origin_f_.x += direct.x / FPS;
    origin_f_.y += direct.y / FPS;
}

void Puck::find_direction(Object *player, Object *bot)
{
    goal_ = false;
    if (clash_pusher(player) == false)
        clash_pusher(bot);
    if (origin_f_.x <= LEFT_WALL + radius_ ||//отбивается от левой стенки
        origin_f_.x >= RIGHT_WALL - radius_)//отбивается от правой стенки
    {
        if (origin_f_.x < LEFT_WALL + radius_)
            origin_f_.x = LEFT_WALL + radius_;
        if (origin_f_.x > RIGHT_WALL - radius_)
            origin_f_.x = RIGHT_WALL - radius_;
        if (abs(direct.x) > 2.0)
            direct.x *= -1;
        direct.x *= 0.8;
        direct.y *= 0.8;
        music_.play_sound(KICK);
    }
    if (origin_f_.y <= TOP_WALL + radius_ || //отбивается от верхней стенки
        origin_f_.y >= BOTTOM_WALL - radius_)//отбивается от нижней стенки
    {
        if (origin_f_.y < TOP_WALL + radius_)
            origin_f_.y = TOP_WALL + radius_;
        if (origin_f_.y > BOTTOM_WALL - radius_)
            origin_f_.y = BOTTOM_WALL - radius_;
        if (hitting_gate() == false)
        {
            if (abs(direct.y) > 2.0)
                direct.y *= -1;
            direct.y *= 0.9;
            direct.x *= 0.9;
            music_.play_sound(KICK);
        }
    }
}

bool Puck::clash_pusher(Object *obj)
{
    float  distance;
    float  distance1;

    distance = obj->get_radius() + this->get_radius();
    distance1 = find_distance(this, obj);
    if (distance1 - distance < 1 || distance1 < distance)//отбивается
    {
        direct.x += obj->get_direction().x;
        direct.x *= 0.7;
        direct.y += obj->get_direction().y;
        direct.y *= 0.7;
        music_.play_sound(KICK);
        return true;
    }
    return false;
}

bool Puck::hitting_gate()
{
    if ((origin_f_.x - get_radius() > window_edge_.x + WIN_WIDTH / 2 - HALF_GATE) &&
        (origin_f_.x + get_radius() < window_edge_.x + WIN_WIDTH / 2 + HALF_GATE))
    {
        origin_f_.x = 0;
        music_.play_sound(GOAL);
        goal_ = true;
        return true;
    }
    return false;
}
