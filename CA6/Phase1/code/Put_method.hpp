#ifndef PUT_METHOD
#define PUT_METHOD

#include <string>
#include "method.hpp"
#include "UT_post.hpp"


class Put : public Method
{
public:
    Put(std::string t , std::vector <std::string> cmds);
	void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
                        ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response);
};

#endif