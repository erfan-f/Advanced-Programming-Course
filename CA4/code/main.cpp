#include "car_wash.h"

const string Command_Type_1 = "pass_time";
const string Command_Type_2 = "car_arrival";
const string Command_Type_3 = "get_stage_status";
const string Command_Type_4 = "get_worker_status";
const string Command_Type_5 = "get_car_status";

void Command_Process(Car_Wash &car_wash);


int main(int argc ,char *argv[])
{

	Car_Wash car_wash;

	car_wash.read_from_files(argv[1] , argv[2]);

	Command_Process(car_wash);

	return 0;
}

void Command_Process(Car_Wash &car_wash)
{
	string command_line;
	string command;
	string id;
	vector <string> command_num;

	while(getline(cin,command_line))
	{
		stringstream S(command_line);
		S >> command;

		if(command == Command_Type_2)
		{
			while(S >> id)
			{
				command_num.push_back(id);
			}
			car_wash.Add_Car(command_num);
			command_num.clear();
		}
		else if(command == Command_Type_1)
		{
			S >> id;
			car_wash.through_time(stoi(id));
		}
		else if(command == Command_Type_3 )
		{
			S >> id;
			car_wash.get_stage_status(id);
		}
		else if(command == Command_Type_4)
		{
			S >> id;
			car_wash.get_worker_status(id);
		}
		else if(command == Command_Type_5)
		{
			S >> id;
			car_wash.get_car_status(id);
		}
	}
}