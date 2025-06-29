#include "car_wash.h"

void Car_Wash::read_from_files(string stage_path , string workers_path)
{
	read_stages(stage_path);
	read_workers(workers_path);
}
void Car_Wash::read_stages(string path)
{
	string ID;
	string price;

	fstream fin;
	fin.open(path,ios::in);

	string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		stringstream S(temp_str);
		getline(S,ID,Seprator);
		getline(S,price,Seprator);
		Add_Stage(ID,stof(price));
	}	 

fin.close();
}
void Car_Wash::read_workers(string path)
{
	string ID;
	string stage_id;
	string Time_to_finish;

	fstream fin;
	fin.open(path,ios::in);

	string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		stringstream S(temp_str);
		getline(S,ID,Seprator);
		getline(S,stage_id,Seprator);
		getline(S,Time_to_finish,Seprator);
		Add_Worker(ID,stage_id,stoi(Time_to_finish));
	}
}
void Car_Wash::Add_Stage(string ID , float Price)
{
	stages.push_back(new Stage(ID,Price));
}

void Car_Wash::Add_Worker(string ID , string stage_id , int Time_to_finish)
{
	Worker * w = new Worker(ID , stage_id , Time_to_finish);
	workers.push_back(w);
	for(int i=0 ; i<stages.size() ; i++) 
	{
		if(stages[i]->get_id() == stage_id)
			stages[i]->Add_Worker(w);
	}
	for(int i=0 ; i<stages.size() ; i++)
		stages[i]->sort_worker();	
}
void Car_Wash::Add_Car(vector<string> stages_id )
{
	Car *car = new Car (to_string(cars.size() + 1), Primary_situation ,stages_id);
	cars.push_back(car);
	apply_stage(to_string(cars.size()) , Primary_situation);
}

void Car_Wash::get_stage_status(string stage_id)
{
	Stage *stage = find_stage(stage_id);
	if(stage)
		stage->get_report();
	else
		cout << "NOT FOUND" << endl;
	
}

void Car_Wash::get_worker_status(string worker_id)
{
	Worker *worker = find_worker(worker_id);
	if(worker)
		worker->get_report();
	else 
		cout << "NOT FOUND" << endl;
}

void Car_Wash::get_car_status(string car_id)
{
	Car *car = find_car(car_id);
	if(car)
		car->get_report();
	else
		cout << "NOT FOUND" << endl;

}

Car* Car_Wash::find_car(string car_id)
{
	Car *car = NULL;
	for(int i = 0 ; i<cars.size() ; i++)
	{
		if(cars[i]->get_id() == car_id)
		{
			car = cars[i];
			break;
		}
	}
	return car;
}

Stage* Car_Wash::find_stage(string stage_id)
{
	Stage *stage = NULL;
	for(int j=0 ; j<stages.size() ; j++)
	{
		if(stages[j]->get_id() == stage_id)
		{
			stage = stages[j];
			break;
		}
	}
	return stage;
}

Worker* Car_Wash::find_worker(string worker_id)
{
	Worker *worker = NULL;
	for(int i=0 ; i < workers.size() ; i++)
	{
		if(workers[i]->get_id() == worker_id)
		{
			worker = workers[i];
			break;
		}
	}
	return worker;
}
bool Car_Wash::is_worker_found(Stage *stage , string car_id)
{
	vector<Worker*> workers_list = stage->get_workers_list();
	for(int i=0 ; i<workers_list.size() ; i++)
	{
		if(workers_list[i]->is_free())
		{
			return true;
		}
	}
	return false;
}

Worker* Car_Wash::found_worker(Stage *stage , string car_id)
{
	vector<Worker*> workers_list = stage->get_workers_list();
	Worker *worker;
	for(int i=0 ; i<workers_list.size() ; i++)
	{
		if(workers_list[i]->is_free())
		{
			worker = workers_list[i];
			break;
		}
	}
	return worker;
}

void Car_Wash::through_time(int dt)
{
	for(int i=0 ; i<dt ; i++)
	{
		time++;
		check_operation();
		
	}
}
void Car_Wash::check_operation()
{

	for(int i=0 ; i<cars.size() ; i++)
	{
		if(cars[i]->is_in_service())
		{
			if(cars[i]->is_pass(time))
			{
				Stage *previous_stage = find_stage(cars[i]->get_current_stage_id());
				cars[i]->out_from_stage();
				previous_stage->car_go_out_stage(cars[i]);
				apply_stage(cars[i]->get_id(),cars[i]->get_status());
			}
		}
		else if(cars[i]->is_in_line())
		{
			Stage *stage = find_stage(cars[i]->get_current_stage_id());
			if(is_worker_found(stage , cars[i]->get_id()))
			{
				apply_stage(cars[i]->get_id(),cars[i]->get_status());
			}
		}

	}

}
void Car_Wash::apply_stage(string car_id , string car_status)
{
	if(car_status == Primary_situation)
	{
		arrived_report(car_id);
	}
	else if(car_status == Car_Status_2 || car_status == Car_Status_3)
	{
		stage_to_stage_report(car_id);
	}
	else if(car_status == Car_Status_1)
	{
		queue_to_stage_report(car_id);
	}

}

void Car_Wash::arrived_report(string car_id)
{
	Car *car = find_car(car_id);

	Stage *current_stage = find_stage(car->get_current_stage_id());

	if(is_worker_found(current_stage,car_id))
	{
		Worker *worker = found_worker(current_stage,car_id); 
		worker->apply_car(car_id , time);
		current_stage->car_in(car);
		car->change_status(Car_Status_2);
		car->change_worker(worker);

		ostringstream OSS;
		OSS << time << " Car " << car_id << ": "  << Primary_situation << " -> Stage " << current_stage->get_id();
		string report = OSS.str();
		cout << report << endl;
	}
	else
	{
		current_stage->car_in_queue(car);
		car->change_status(Car_Status_1);
		ostringstream OSS;
		OSS << time << " Car " << car_id << ": "  << Primary_situation << " -> Queue " << current_stage->get_id();
		string report = OSS.str(); 
		cout << report << endl;
	}
}

void Car_Wash::queue_to_stage_report(string car_id)
{
	Car *car = find_car(car_id);
	Stage *stage = find_stage(car->get_current_stage_id());

	Worker *worker = found_worker(stage , car_id);
	worker->apply_car(car_id , time);
	car->change_status(Car_Status_2);
	car->change_worker(worker);
	stage->car_go_out_line(car);

	ostringstream OSS;
	OSS << time << " Car " << car_id << ": "  << "Queue " << stage->get_id() << " -> Stage " << stage->get_id();
	string report = OSS.str();
	cout << report << endl;
}
void Car_Wash::stage_to_stage_report(string car_id)
{
	Car *car = find_car(car_id);
	string previous_stage_id = car->get_previous_stage();

	if(car->is_done())
	{
		ostringstream OSS;
		OSS << time << " Car " << car_id << ": "  << "Stage " << previous_stage_id << " -> " << Car_Status_3; 
		string report = OSS.str();
		cout << report << endl;
	}	
	else
	{
		Stage *new_stage = find_stage(car->get_current_stage_id());
		if(is_worker_found(new_stage , car_id))
		{
			Worker *worker = found_worker(new_stage , car_id);
			worker->apply_car(car_id , time);
			new_stage->car_in(car);
			car->change_worker(worker);

			ostringstream OSS;
			OSS << time << " Car " << car_id << ": "  << "Stage " << previous_stage_id << " -> Stage " << new_stage->get_id();
			string report = OSS.str();
			cout << report << endl;
		}
		else
		{
			new_stage->car_in_queue(car);
			car->change_status(Car_Status_1);
			ostringstream OSS;
			OSS << time << " Car " << car_id << ": "  << "Stage " << previous_stage_id << " -> Queue " << new_stage->get_id();
			string report = OSS.str(); 
			cout << report << endl;
		}
	}
}
