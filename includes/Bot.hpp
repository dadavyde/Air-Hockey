#ifndef AIRHOCKEY_BOT_HPP
#define AIRHOCKEY_BOT_HPP

#include "headers.hpp"

#include "Object.hpp"

class Bot : public Object
{
public:
	Bot();
	void 	find_origin() override;
	void 	find_direction(Object *player, Object *bot) override ;

};


#endif
