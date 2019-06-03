#ifndef AIRHOCKEY_PUCK_HPP
#define AIRHOCKEY_PUCK_HPP

#include "math_functions.hpp"

#define SPEED_SHIFT (0.01)

class Puck : public Object
{
public:
	Puck();
	void 	find_origin() override;
	void 	find_direction(Object *player, Object *bot) override ;




};


#endif //AIRHOCKEY_PUCK_HPP
