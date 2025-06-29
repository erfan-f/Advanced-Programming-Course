#include "functions.hpp"

void Command_Operator(SystemController &engine)
{
	IOHandler io_handler;
	std::string command_line;
	std::vector <std::string> response;

	
	while(io_handler.get_Command_Line(command_line))
	{
		try
		{
			engine.Handle_Cmd(command_line,response);
		}
		catch(std::runtime_error &ex)
		{
			io_handler.Print_Error(ex.what());
		}
		io_handler.Print_Data(response);
		response.clear();
	}

}
