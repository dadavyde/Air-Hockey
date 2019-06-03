#ifndef AIRHOCKEY_PLAYER_HPP
#define AIRHOCKEY_PLAYER_HPP

#include "headers.hpp"
#include "Object.hpp"

class Player : public Object
{
public:
    Player();
    void 	find_origin() override;
	void 	find_direction(Object *player, Object *bot) override ;
};


#endif //AIRHOCKEY_PLAYER_HPP
