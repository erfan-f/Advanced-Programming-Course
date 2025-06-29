#include "major.hpp"

Major::Major(std::string n , std::string i)
{
	name = n;
	id =i;
}

bool Major::is_Valid_Id(std::string i)
{
	if(id == i)
		return true;
	return false;
}

std::string Major::get_Name()
{
	return name;
}
