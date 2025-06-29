#include "square.h"

Square::Square(float x , float y , std::string l_i , std::string i)
{
	x_position = x;
	y_position = y;
	free = true;
	line_id = l_i;
	id = i;

}

bool Square:: is_Free(Plant *p)
{
	if(free == true)
	{
		current_plant = p;
		free = false;
		return true;
	}
	else
		return false;
}
std::string Square::get_id()
{
	return id;
}

void Square::Clean()
{
	free = true;
}