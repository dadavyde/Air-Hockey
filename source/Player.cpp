#include "Player.hpp"

Player::Player() : Object()
{
	edge_pos_ = (SDL_Rect){700, 900, 0, 0};
}

void Player::find_origin()//global position
{
	old_origin_f_ = origin_f_;
	if (origin_.x < window_edge_.x + (WIN_WIDTH - TABLE_WIDTH) / 2 + PLAYER_SHIFT2)
		origin_.x = window_edge_.x + (WIN_WIDTH - TABLE_WIDTH) / 2 + PLAYER_SHIFT2;
	else if (origin_.x > window_edge_.x + (WIN_WIDTH + TABLE_WIDTH) / 2 - PLAYER_SHIFT2)//edge_pos_.w
		origin_.x = window_edge_.x + (WIN_WIDTH + TABLE_WIDTH) / 2 - PLAYER_SHIFT2;//edge_pos_.w

	if (origin_.y < window_edge_.y + WIN_HEIGHT / 2 + PLAYER_SHIFT)
		origin_.y = window_edge_.y + WIN_HEIGHT / 2 + PLAYER_SHIFT;
	else if (origin_.y > window_edge_.y + (WIN_HEIGHT + TABLE_HEIGHT) / 2 - edge_pos_.h)
		origin_.y = window_edge_.y + (WIN_HEIGHT + TABLE_HEIGHT) / 2 - edge_pos_.h;
	origin_f_ = (pos_f){static_cast<float>(origin_.x), static_cast<float>(origin_.y)};
}

void 	Player::find_direction(Object *player, Object *bot)
{
	(void)player;
	(void)bot;
	direct.x = (origin_f_.x - old_origin_f_.x) * FPS;
	direct.y = (origin_f_.y - old_origin_f_.y) * FPS;

}