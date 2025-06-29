#include "SystemController.hpp"

SystemController::SystemController()
{
	users.push_back(new SystemOperator(OPERATOR_NAME,OPERATOR_ID,OPERATOR_PASSWORD));

	methods.push_back(new Post(METHOD_1,{USER_CMD_TYPE_1,USER_CMD_TYPE_2,USER_CMD_TYPE_6,USER_CMD_TYPE_4,USER_CMD_TYPE_8}));
	methods.push_back(new Get(METHOD_2,{USER_CMD_TYPE_3,USER_CMD_TYPE_5,USER_CMD_TYPE_4,USER_CMD_TYPE_7,USER_CMD_TYPE_9}));
	methods.push_back(new Put(METHOD_3,{USER_CMD_TYPE_9}));
	methods.push_back(new Delete(METHOD_4,{USER_CMD_TYPE_4,USER_CMD_TYPE_9}));

}


void SystemController::Read_Majors(std::string file_path)
{
	std::string  name,id;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);

		Add_Major(name,id);
	}

}

void SystemController::Read_Units(std::string file_path)
{
	std::string  name,id,credit,prerequisite,majors_id_str;
	std::vector<std::string> majors_id;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,credit,SEPRATOR);
		getline(S,prerequisite,SEPRATOR);
		getline(S,majors_id_str,SEPRATOR);

		std::stringstream S2(majors_id_str);
		while(getline(S2,temp_str,IN_LINE_SEPRATOR))
		{
			majors_id.push_back(temp_str);
		}

		Add_Unit(name,id,std::stoll(credit),prerequisite,majors_id);
		majors_id.clear();
	}
}

void SystemController::Read_Professor(std::string file_path)
{

	std::string  name,id,major,major_id,position,password;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,major_id,SEPRATOR);
		getline(S,position,SEPRATOR);
		getline(S,password,SEPRATOR);

		major = Specify_Major(major_id);

		Add_Professor(name,id,major,major_id,position,password);
	}
}

void SystemController::Read_Student(std::string file_path)
{

	std::string  name,id,major,major_id,semester,password;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,major_id,SEPRATOR);
		getline(S,semester,SEPRATOR);
		getline(S,password,SEPRATOR);

		major = Specify_Major(major_id);
		
		Add_Student(name,id,major,major_id,semester,password);
	}
}



void SystemController::Add_Major(std::string name,std::string id)
{
	Major *m = new Major(name,id);
	majors.push_back(m);
}

void SystemController::Add_Unit(std::string name,std::string id,int credit,std::string prerequisite,std::vector<std::string> majors_id)
{
	Unit *u = new Unit(name,id,credit,prerequisite,majors_id);
	units.push_back(u);
}

void SystemController::Add_Professor(std::string name,std::string id,std::string major,std::string major_id,std::string position,std::string password)
{
	Professor *p = new Professor(name,id,major,major_id,position,password);
	users.push_back(p);
}

void SystemController::Add_Student(std::string name,std::string id,std::string major,std::string major_id,std::string semester,std::string password)
{
	Student *s = new Student(name,id,major,major_id,semester,password);
	users.push_back(s);
}

void SystemController::Handle_Cmd(std::string cmd_line,std::vector<std::string> &response)
{
	std::stringstream S(cmd_line);

	std::string method_type , command , operator_argument;

	S >> method_type;
	S >> command;
	S >> operator_argument;

	Method *method = Specify_Method(method_type);
	

	if(!method->is_Cmd_Valid(command))
	{
		throw CommandException(ERROR_2);
	}
	if(operator_argument != OPERATOR_ARGUMANT)
		throw CommandException(ERROR_1);

	if(command == USER_CMD_TYPE_1 )
	{
		if(current_user != NULL)
			throw AcessibilityException(ERROR_3);

		method->Process_Cmd(cmd_line,majors,units,users,courses,&current_user,response);

	}
	else
	{
		if(current_user == NULL)
			throw AcessibilityException(ERROR_3);
		
		if(current_user->Permision_Check(command))
			method->Process_Cmd(cmd_line,majors,units,users,courses,&current_user,response);
		else	
			throw AcessibilityException(ERROR_3);
	}
	
}

Method* SystemController::Specify_Method(std::string method_type)
{
	for(int i=0 ; i<methods.size() ; i++)
	{
		if(methods[i]->is_Equal(method_type))
		{
			return methods[i];
		}
	}
	throw MethodException(ERROR_1);
}

std::string SystemController::Specify_Major(std::string id)
{

	std::string major;
	for(int i=0 ; i<majors.size() ; i++)
	{
		if(majors[i]->is_Valid_Id(id))
		{
			major = majors[i]->get_Name();
			break;
		}
	}
	return major;
}

void SystemController::Connect_To_All_User()
{
	for(int i=1 ; i<users.size() ; i++)
	{
		users[i]->Connect(users[0]);
		users[0]->Connect(users[i]);
	}
}

void SystemController::Free_Allocated_Memory()
{

	for(int i=0 ; i<users.size()  ; i++)
	{
		users[i]->Free_Allocated_Memory();
		delete users[i];
	}
	for(int i=0 ; i<majors.size() ; i++)
		delete majors[i];
	for(int i=0 ; i<units.size() ; i++)
		delete units[i];
	for(int i=0 ; i<courses.size() ; i++)
	{
		courses[i]->Free_Allocated_Memory();
		delete courses[i];
	}
	for(int i=0 ; i<methods.size() ; i++)
		delete methods[i];
}
