#include "Get_method.hpp"

Get::Get(std::string t , std::vector <std::string> cmds)
:Method(t,cmds) {}

void Get::Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
	std::stringstream S(cmd_line);

	std::string temp_str,command;

	S >> temp_str >> command >> temp_str;

	if(command == USER_CMD_TYPE_3)
	{
		std::string id_argument,id,garbage_string;
		S >> id_argument >> id >> garbage_string;
		if(id_argument == "")
		{
			get_All_Courses_Info(courses,response);
		}
		else
		{
			if(id_argument != CMD_ARGUMENT_1 || id == "")
				throw ArgumentException(ERROR_1);

			if(!is_Number(id))
            	throw ArgumentException(ERROR_1);

			if(std::stoll(id) <= 0)
				throw ArgumentException(ERROR_1);
			if(garbage_string != "")
				throw ArgumentException(ERROR_1);

			get_Course_Info(courses,id,response);
		}
	}
	else if(command == USER_CMD_TYPE_4)
	{
		if( dynamic_cast<SystemOperator*>(*current_user) != NULL)
			throw AcessibilityException(ERROR_3);
		
		std::string argument_1,argument_2,input_1,input_2,garbage_string;
		std::string id,post_id;
		S >> argument_1 >> input_1 >> argument_2 >> input_2 >> garbage_string;
		if((argument_1 == CMD_ARGUMENT_1 || argument_1 == CMD_ARGUMENT_3 ) && (argument_2 == CMD_ARGUMENT_1 || argument_2 == CMD_ARGUMENT_3))
		{
			if(argument_1 == CMD_ARGUMENT_1)
			{
				id = input_1;
				post_id = input_2;
			}
			else
			{
				id = input_2;
				post_id = input_1;
			}
		}
		else
			throw ArgumentException(ERROR_1);

		if(!is_Number(id) || !is_Number(post_id))
            throw ArgumentException(ERROR_1);

		if(std::stoll(id) <0 || std::stoll(post_id) <=0)
			throw ArgumentException(ERROR_1);
		
		if(garbage_string != "")
			throw ArgumentException(ERROR_1);

		get_User_Post(users,id,post_id,response);
	}
	else if(command == USER_CMD_TYPE_5)
	{
		std::string id_argument,id,garbage_string;
		S >> id_argument >> id >> garbage_string;
		if(id_argument != CMD_ARGUMENT_1 || id == "")
			throw ArgumentException(ERROR_1);

		if(!is_Number(id))
            throw ArgumentException(ERROR_1);
		if(std::stoll(id) < 0)
			throw ArgumentException(ERROR_1);
		if(garbage_string != "")
			throw ArgumentException(ERROR_1);

		get_Personal_Page(users,id,response);
	}
	else if(command == USER_CMD_TYPE_7)
	{
		std::string argument_str;
		S >> argument_str;
		
		if(argument_str != "")
			throw ArgumentException(ERROR_1);
		
		response.push_back((*current_user)->get_Notifications());
	}
	else if(command == USER_CMD_TYPE_9)
	{
		std::string argument_str;
		S >> argument_str;
		if(argument_str != "")
			throw ArgumentException(ERROR_1);

		Student *student = dynamic_cast<Student*>(*current_user);
		if(student == NULL)
            throw AcessibilityException(ERROR_3);

		response.push_back(student->get_Courses_Info());
	}
}


void Get::get_All_Courses_Info(std::vector<Course*> courses , std::vector<std::string> &response)
{	
	if(courses.size() == 0)
		throw CommandException(ERROR_4);

	for(int i=0 ; i<courses.size(); i++)
	{
		response.push_back(courses[i]->get_Info());
	}
	
}

void Get::get_Course_Info(std::vector<Course*> courses , std::string course_id,std::vector<std::string> &response)
{
	Course *target_course = Find_Course(courses,course_id);
	
	response.push_back(target_course->get_All_Info());
}


void Get::get_Personal_Page(std::vector<User*> users,std::string user_id,std::vector<std::string> &response)
{
	User *user = Find_User(users,user_id);

	response.push_back(user->get_Page_Info());
}

void Get::get_User_Post(std::vector<User*> users,std::string user_id,std::string post_id,std::vector<std::string> &response)
{
	User *user = Find_User(users,user_id);
	
	response.push_back(user->get_Post(post_id));
}
