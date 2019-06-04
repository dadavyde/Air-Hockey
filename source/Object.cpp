#include "Object.hpp"

Object::Object() : edge_pos_(), origin_(), origin_f_(), old_origin_f_(), direct(), window_edge_(), music_()
{
//	edge_pos_ = (SDL_Rect){0, 0, 0, 0};
//	origin_ = (pos){0, 0};
//	origin_f_ = (pos_f){0, 0};
//	direct = (vector){0, 0};
//	window_edge_ = (pos){0, 0};
}

Object& Object::operator=(const Object &other)
{
	if (this != &other)
	{
		this->edge_pos_ = other.edge_pos_;
		this->origin_ = other.origin_;
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
	edge_pos_.x = origin_.x - window_edge_.x - edge_pos_.w / 2;
	edge_pos_.y = origin_.y - window_edge_.y - edge_pos_.h / 2;
}

SDL_Rect* Object::get_edge_pos()
{
	return &edge_pos_;
}

void Object::set_sizes(int h, int w)
{
	edge_pos_.h = h;
	edge_pos_.w = w;
}

void Object::set_origin(pos origin)
{
	origin_ = origin;
}

pos Object::get_origin()
{
	return origin_;
}

void Object::set_origin_f(float x, float y)
{
	origin_f_ = (pos_f){x, y};
}

pos_f Object::get_origin_f()
{
	return origin_f_;
}

float Object::get_radius()
{
	return (static_cast<float>(edge_pos_.w) / 2);
}

void Object::set_direction(float x, float y)
{
	direct.x = x;
	direct.y = y;
}

vector Object::get_direction()
{
	return direct;
}

void Object::set_win_edge_pos(pos window_edge)
{
	window_edge_ = window_edge;
}

void Object::set_music(Music &music)
{
	music_ = music;
}
