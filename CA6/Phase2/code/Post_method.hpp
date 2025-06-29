#ifndef POST
#define POST

#include <string>
#include "method.hpp"
#include "UT_media.hpp"


class Post : public Method
{
public:
	Post(std::string t , std::vector <std::string> cmds);
	~Post();
	void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
						,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response);

private:
	void Connect_Two_User(std::vector<User*> &users , std::string target_id ,User **current_user);
	void Send_Public_Notification(std::vector<User*> users,std::string id,std::string name,std::string notice_text);
	void Send_Channel_Notification(std::vector<User*> users,std::vector<std::string> participants_id,std::string course_id,std::string course_name);
	void TA_Admission(std::vector<User*> users,std::vector<std::string> volunteers_id,Course *course);
	std::string Text_Reader(std::string &cmd_line);
	User* User_Login(std::vector<User*> &users , std::string id , std::string password);

};

#endif