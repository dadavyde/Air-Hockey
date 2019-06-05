#include "Object.hpp"

Object::Object() : edge_pos_(), origin_f_(), old_origin_f_(), direct(), window_edge_(), music_(), radius_(), goal_()
{}

Object& Object::operator=(const Object &other)
{
    if (this != &other)
    {
        this->edge_pos_ = other.edge_pos_;
        this->origin_f_ = other.origin_f_;
        this->old_origin_f_ = other.old_origin_f_;
        this->direct = other.direct;
        this->window_edge_ = other.window_edge_;
        this->music_ = other.music_;
    }
    return *this;
}

Object::Object(const Object &other)
{
    *this = other;
}

void Object::set_edge_pos()
{
    find_origin();
    edge_pos_.x = static_cast<int>(origin_f_.x) - window_edge_.x - static_cast<int>(radius_);
    edge_pos_.y = static_cast<int>(origin_f_.y) - window_edge_.y - static_cast<int>(radius_);
}

SDL_Rect* Object::get_edge_pos()
{
    return &edge_pos_;
}

void Object::set_sizes(int h, int w)
{
    edge_pos_.h = h;
    edge_pos_.w = w;
    radius_ = static_cast<float>(w) / 2;
}

void  Object::set_origin_f(float x, float y)
{
    old_origin_f_ = origin_f_;
    if (x != -1)
        origin_f_.x = x;
    if (y != -1)
        origin_f_.y = y;
}

pos_f  Object::get_origin_f()
{
    return origin_f_;
}

void  Object::set_old_origin_f(pos_f origin)
{
    old_origin_f_ = origin;
}

float  Object::get_radius()
{
    return (radius_);
}

void  Object::set_direction(float x, float y)
{
    direct.x = x;
    direct.y = y;
}

vector  Object::get_direction()
{
    return direct;
}

void  Object::set_win_edge_pos(pos window_edge)
{
    window_edge_ = window_edge;
}

void  Object::set_music(Music &music)
{
    music_ = music;
}

bool  Object::is_goal()
{
    return goal_;

}