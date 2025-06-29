#ifndef SQUARE
#define SQUARE

#include <string>
#include "plant.h"

const int NUM_OF_SQUARE = 9;
const float SQUARE_LENGTH = 72;


class Square
{
private:

	bool free;
	Plant *current_plant;

public:
	std::string id;
	std::string line_id;
	float x_position;
	float y_position;
	Square(float x , float y , std::string l_i , std::string i);
	std::string get_id();
	bool is_Free(Plant *p);
	void Clean();

};


#endif