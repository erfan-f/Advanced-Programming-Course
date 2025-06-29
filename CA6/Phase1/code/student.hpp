#ifndef STUDENT
#define STUDENT

#include <string>
#include "user.hpp"


class Student : public User 
{
public:
	Student(std::string n,std::string i,std::string m,std::string m_i,std::string s,std::string p);
	std::string get_Info();
	std::string get_Page_Info();
	bool is_Allowed_to_Take(Course* new_course);
	std::string get_Courses_Info();
	void Delete_Course(std::string course_id);

private:
	std::string semester;

};

#endif