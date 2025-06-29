#include <iostream>
#include "SystemController.hpp"
#include "functions.hpp"



int main(int argc ,char *argv[])
{
	SystemController engine = SystemController();

	engine.Read_Majors(argv[1]);
	engine.Read_Units(argv[2]);
	engine.Read_Professor(argv[3]);
	engine.Read_Student(argv[4]);

	engine.Connect_To_All_User();
	
	Command_Operator(engine);

	engine.Free_Allocated_Memory();

	return 0;
}