#include "Delete_method.hpp"

Delete::Delete(std::string t , std::vector <std::string> cmds)
:Method(t,cmds) {}

void Delete::Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
    std::stringstream S(cmd_line);

	std::string temp_str,command;

	S >> temp_str >> command >> temp_str;

    if(command == USER_CMD_TYPE_4)
    {
        std::string id_operator,id,garbage_string;

        S >> id_operator >> id >> garbage_string;
        
        if(id_operator != CMD_ARGUMENT_1 || id == "")
            throw ArgumentException(ERROR_1);

        if(!is_Number(id))
            throw ArgumentException(ERROR_1);

        if(std::stoll(id) <= 0)
            throw ArgumentException(ERROR_1);

        if(garbage_string != "")
            throw ArgumentException(ERROR_1);

        (*current_user)->Delete_Post(id);
        
        std::ostringstream os;
        os << DONE_MESSAGE << std::endl;
        response.push_back(os.str());
    }
    else if(command == USER_CMD_TYPE_9)
    {
         std::string id_operator,id,garbage_string;

        S >> id_operator >> id >> garbage_string;
        
        if(id_operator != CMD_ARGUMENT_1 || id == "")
            throw ArgumentException(ERROR_1);

        if(!is_Number(id))
            throw ArgumentException(ERROR_1);

        if(std::stoll(id) <= 0)
            throw ArgumentException(ERROR_1);

        if(garbage_string != "")
            throw ArgumentException(ERROR_1);

        Student* student= dynamic_cast<Student*>(*current_user);
        if(student == NULL)
            throw AcessibilityException(ERROR_3);
            
        student->Delete_Course(id);

        std::ostringstream os;
        os << DONE_MESSAGE << std::endl;
        response.push_back(os.str());
    }
}

