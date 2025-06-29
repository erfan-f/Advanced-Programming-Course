#include "SystemOperator.hpp"

SystemOperator::SystemOperator(std::string n , std::string i , std::string pass)
:User(n,i,pass) 
{
	user_type = USER_TYPE_3;

    valid_cmds.push_back(USER_CMD_TYPE_1);
	valid_cmds.push_back(USER_CMD_TYPE_2);
	valid_cmds.push_back(USER_CMD_TYPE_4);
	valid_cmds.push_back(USER_CMD_TYPE_8);

}

std::string SystemOperator::get_Info()
{	
	std::ostringstream S;
	S << name << std::endl;
	return S.str();
}

std::string SystemOperator::get_Page_Info()
{
	std::ostringstream S;
	S << get_Info();
	
	Sort_Posts();
	for(int j=0 ; j<posts.size() ; j++)
	{
		S <<  posts[j]->id << SPACE_CHAR << posts[j]->title << std::endl;
	}
	return S.str();
}