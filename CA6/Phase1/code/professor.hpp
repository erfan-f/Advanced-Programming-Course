#ifndef PROFESSOR
#define PROFESSOR
#include <string>
#include "user.hpp"

class Professor : public User 
{
public:
	Professor(std::string n,std::string i,std::string m,std::string m_i,std::string po,std::string p);
	void Add_New_Course(Course *new_course);
	bool is_Free(std::string time);
	std::string get_Info();
	std::string get_Page_Info();

private:
	std::string position;
};


#endif