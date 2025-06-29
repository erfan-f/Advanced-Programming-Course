#ifndef DELETE
#define DELETE

#include <string>
#include "method.hpp"
#include "UT_post.hpp"

class Delete : public Method
{
public:
    Delete(std::string t , std::vector <std::string> cmds);
	void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
                        ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response);
};

#endif