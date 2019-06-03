#ifndef AIRHOCKEY_OBJECT_HPP
#define AIRHOCKEY_OBJECT_HPP

#include "headers.hpp"

class Object
{
public:
	Object();
	~Object() = default;
	Object &operator=(const Object &other);
	Object(const Object &other);

	virtual void 	find_origin() = 0;
	virtual void 	find_direction(Object *player, Object *bot) = 0;
	void  			set_edge_pos();
	SDL_Rect*  		get_edge_pos();
	void  			set_sizes(int h, int w);
	float  			get_radius();
	void			set_origin(pos origin);
	pos				get_origin();
	void 			set_origin_f(float x, float y);
	pos_f			get_origin_f();
	void			set_direction(float x, float y);
	vector			get_direction();
	void  			set_win_edge_pos(pos window_edge);

protected:
	SDL_Rect  	edge_pos_;
	pos  		origin_;
	pos_f  		origin_f_;
	pos_f  		old_origin_f_;
	vector		direct;//вектор направления передвижения в секунду
	pos			window_edge_;
};


#endif
