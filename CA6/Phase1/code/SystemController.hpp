#ifndef SYSTEM_CONTROLLER
#define SYSTEM_CONTROLLER

#include "iostream"
#include <vector>
#include <fstream>
#include <sstream>

#include "exception.hpp"
#include "major.hpp"
#include "unit.hpp"
#include "user.hpp"
#include "professor.hpp"
#include "student.hpp"
#include "messages.hpp"
#include "SystemOperator.hpp"
#include "course.hpp"
#include "Post_method.hpp"
#include "Get_method.hpp"
#include "Put_method.hpp"
#include "Delete_method.hpp"


const std::string OPERATOR_NAME = "UT_account";
const std::string OPERATOR_ID = "0";
const std::string OPERATOR_PASSWORD = "UT_account";

const char SEPRATOR = ',';
const char IN_LINE_SEPRATOR = ';';

const int NUM_OF_METHOD = 4;
const std::string METHOD_1 = "POST";
const std::string METHOD_2 = "GET";
const std::string METHOD_3 = "PUT";
const std::string METHOD_4 = "DELETE";

const std::string OPERATOR_ARGUMANT = "?";



class SystemController
{
public:
	SystemController();
	void Read_Majors(std::string file_path);
	void Read_Units(std::string file_path);
	void Read_Professor(std::string file_path);
	void Read_Student(std::string file_path);
	void Connect_To_All_User();
	void Add_Major(std::string name,std::string id);
	void Add_Unit(std::string name,std::string id,int credit,std::string prerequisite,std::vector<std::string> majors_id);
	void Add_Professor(std::string name,std::string id,std::string major,std::string major_id,std::string position,std::string password);
	void Add_Student(std::string name,std::string id,std::string major,std::string major_id,std::string semester,std::string password);
	void Handle_Cmd(std::string cmd_line,std::vector<std::string> &response);
	Method* Specify_Method(std::string method_type);
	std::string Specify_Major(std::string id);
	void Free_Allocated_Memory();

private:
	std::vector<User*> users;
	std::vector<Major*> majors;
	std::vector<Unit*> units;
	std::vector<Course*> courses;
	std::vector<Method*> methods;
	std::vector<std::string> user_cmds;
	User *current_user;
};

#endif