#include "functions.hpp"

void Command_Operator(SystemController &engine)
{
	std::string command_line;
	std::vector <std::string> response;

	while(getline(std::cin,command_line))
	{
		try
		{
			engine.Handle_Cmd(command_line,response);
		}
		catch(std::runtime_error &ex)
		{
			std::cerr << ex.what() << std::endl;
		}
		for(int i=0 ; i<response.size() ; i++)
			std::cout << response[i] ;
		response.clear();
	}

}
