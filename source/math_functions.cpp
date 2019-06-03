#include "math_functions.hpp"

float find_distance(Object *obj1, Object *obj2)
{
	return (sqrtf(squared(obj1->get_origin_f().x - obj2->get_origin_f().x) + squared(obj1->get_origin_f().y - obj2->get_origin_f().y)));
}

float  squared(float a)
{
	return (a * a);
}


