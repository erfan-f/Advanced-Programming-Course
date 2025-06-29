#include "professor.hpp"

Professor::Professor(std::string n,std::string i,std::string m,std::string m_i,std::string po,std::string p)
:User(n,i,m,m_i,p)
{
	position = po;
	user_type = USER_TYPE_1;

	valid_cmds.push_back(USER_CMD_TYPE_1);
	valid_cmds.push_back(USER_CMD_TYPE_2);
	valid_cmds.push_back(USER_CMD_TYPE_3);
	valid_cmds.push_back(USER_CMD_TYPE_4);
	valid_cmds.push_back(USER_CMD_TYPE_5);
	valid_cmds.push_back(USER_CMD_TYPE_6);
	valid_cmds.push_back(USER_CMD_TYPE_7);

}


void Professor::Add_New_Course(Course *new_course)
{
	courses.push_back(new_course);
}

bool Professor::is_Free(std::string time)
{
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Interrupted(time))
			return false;
	}
	return true;
}


std::string Professor::get_Info()
{
	std::ostringstream S;
	S << name << SPACE_CHAR << major << SPACE_CHAR << position << SPACE_CHAR;
	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_Name();
		if(i != courses.size() - 1)
			S << WORD_SEPRATOR;
	}

	S << std::endl;

	return S.str();
}

std::string Professor::get_Page_Info()
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









