#ifndef GET
#define GET

#include <string>
#include "method.hpp"

class Get : public Method
{
public:
	Get(std::string t , std::vector <std::string> cmds);
	void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
						,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response);
	void get_All_Courses_Info(std::vector<Course*> courses,std::vector<std::string> &response);
	void get_Course_Info(std::vector<Course*> courses , std::string course_id,std::vector<std::string> &response);
	void get_Personal_Page(std::vector<User*> users,std::string user_id,std::vector<std::string> &response);
	void get_User_Post(std::vector<User*> users,std::string user_id,std::string post_id,std::vector<std::string> &response);

};

#endif