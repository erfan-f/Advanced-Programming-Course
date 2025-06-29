#include "student.hpp"

Student::Student(std::string n,std::string i,std::string m,std::string m_i,std::string s,std::string p)
:User(n,i,m,m_i,p)
{
	semester = s;
	user_type = USER_TYPE_2;

	valid_cmds.push_back(USER_CMD_TYPE_1);
	valid_cmds.push_back(USER_CMD_TYPE_2);
	valid_cmds.push_back(USER_CMD_TYPE_3);
	valid_cmds.push_back(USER_CMD_TYPE_4);
	valid_cmds.push_back(USER_CMD_TYPE_5);
	valid_cmds.push_back(USER_CMD_TYPE_6);
	valid_cmds.push_back(USER_CMD_TYPE_7);
	valid_cmds.push_back(USER_CMD_TYPE_9);
}

std::string Student::get_Info()
{
	std::ostringstream S;
	S << name << SPACE_CHAR << major << SPACE_CHAR << semester << SPACE_CHAR;
	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_Name();
		if(i != courses.size() - 1)
			S << WORD_SEPRATOR;
	}
	S << std::endl;
	return S.str();
}

std::string Student::get_Page_Info()
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

bool Student::is_Allowed_to_Take(Course* new_course)
{
	if(!new_course->is_Valid_Semester(semester))
		return false;
	if(!new_course->is_Valid_Major(major_id))
		return false;
	
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Interrupted(new_course))
			return false;
	}

	Send_Notification(NOTIFICATION_3);
	courses.push_back(new_course);

	return true;
}

void Student::Delete_Course(std::string course_id)
{
	bool id_validation = false;
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Valid_Id(course_id))
		{
			id_validation = true;
			courses.erase(courses.begin() + i);
			Send_Notification(NOTIFICATION_4);
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(ERROR_2);
}


std::string Student::get_Courses_Info()
{
	std::ostringstream S;

	if(courses.size() == 0)
		throw AvailabilityException(ERROR_4);

	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_All_Info();
	}
	return S.str();
}
