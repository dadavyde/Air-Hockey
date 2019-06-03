#include "Puck.hpp"

Puck::Puck() : Object()
{
	origin_f_ = (pos_f){1200, 800};
}

void Puck::find_origin()
{
	origin_f_.x += direct.x / FPS;
	origin_f_.y += direct.y / FPS;
	origin_ = (pos){static_cast<int>(lround(origin_f_.x)), static_cast<int>(lround(origin_f_.y))};
}

void Puck::find_direction(Object *player, Object *bot)
{
	float  distance;
	float  distance1;

	distance = player->get_radius() + this->get_radius();
	distance1 = find_distance(this, player);
	if (distance1 - distance < 1 || distance1 < distance)
	{
		this->direct.x += player->get_direction().x;
		this->direct.y += player->get_direction().y;
	}
	distance = bot->get_radius() + this->get_radius();
	distance1 = find_distance(this, bot);
	if (distance1 - distance < 1 || distance1 < distance)
	{
		this->direct.x += bot->get_direction().x;
		this->direct.y += bot->get_direction().y;
	}
	if ((origin_f_.x - get_radius() - window_edge_.x - (WIN_WIDTH - TABLE_WIDTH) / 2 < 0.1) ||
		(window_edge_.x + (WIN_WIDTH + TABLE_WIDTH) / 2 - origin_f_.x - get_radius() < 0.1))//отбивается от правой или левой стенки
	{
		if (abs(direct.x) > 2.0)
			direct.x *= -1;
		direct.x *= 0.9;
		direct.y *= 0.9;
	}
	if ((origin_f_.y - get_radius() - window_edge_.y - (WIN_HEIGHT - TABLE_HEIGHT) / 2 < 0.1) || //верхняя граница или нижняя
			 (window_edge_.y + (WIN_WIDTH + TABLE_WIDTH) / 2 - origin_f_.y - get_radius() < 0.1))
	{
		if ((origin_f_.x - get_radius() > window_edge_.x + WIN_WIDTH / 2 - HALF_GATE) &&
			(origin_f_.x + get_radius() < window_edge_.x + WIN_WIDTH / 2 + HALF_GATE))//ворота
		{
			origin_f_.x = 0;
			origin_.x = 0;
		}
		else
		{
			if (abs(direct.y) > 2.0)
				direct.y *= -1;
			direct.y *= 0.9;
			direct.x *= 0.9;
		}
	}
}