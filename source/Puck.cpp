#include "Puck.hpp"

Puck::Puck() : Object()
{
	origin_f_ = (pos_f){1100, 800};
}

void Puck::find_origin()
{
	origin_f_.x += direct.x / FPS;
	origin_f_.y += direct.y / FPS;
	origin_ = (pos){static_cast<int>(lround(origin_f_.x)), static_cast<int>(lround(origin_f_.y))};
}

void Puck::find_direction(Object *player, Object *bot)
{
	if (clash_pusher(player) == false)
		clash_pusher(bot);
	if ((origin_f_.x - get_radius() - window_edge_.x - (WIN_WIDTH - TABLE_WIDTH) / 2 < 0.1) ||
		(window_edge_.x + (WIN_WIDTH + TABLE_WIDTH) / 2 - origin_f_.x - get_radius() < 0.1))//отбивается от правой или левой стенки
	{
		if (abs(direct.x) > 2.0)
			direct.x *= -1;
		direct.x *= 0.9;
		direct.y *= 0.9;
		music_.play_sound(KICK);
	}
	if ((origin_f_.y - get_radius() - window_edge_.y - (WIN_HEIGHT - TABLE_HEIGHT) / 2 < 0.1) || //верхняя граница или нижняя
			 (window_edge_.y + (WIN_WIDTH + TABLE_WIDTH) / 2 - origin_f_.y - get_radius() < 0.1))
	{
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
		this->direct.x += obj->get_direction().x;
		this->direct.y += obj->get_direction().y;
		music_.play_sound(KICK);
		return true;
	}
	return false;
}

bool Puck::hitting_gate()
{
	if ((origin_f_.x - get_radius() > window_edge_.x + WIN_WIDTH / 2 - HALF_GATE) &&
		(origin_f_.x + get_radius() < window_edge_.x + WIN_WIDTH / 2 + HALF_GATE))//ворота
	{
		origin_f_.x = 0;
		origin_.x = 0;
		music_.play_sound(GOAL);
		return true;
	}
	return false;
}
