#ifndef AIRHOCKEY_PUCK_HPP
#define AIRHOCKEY_PUCK_HPP

#include "math_functions.hpp"

class Puck : public Object
{
public:
	Puck();
	void 	find_origin() override;
	void 	find_direction(Object *player, Object *bot) override ;
	bool	clash_pusher(Object *obj);
	bool	hitting_gate();
};


#endif //AIRHOCKEY_PUCK_HPP
