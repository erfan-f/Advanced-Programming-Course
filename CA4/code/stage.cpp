#include "stage.h"


Stage::Stage(string i , float p)
{
	ID = i;
	price = p;
	income = 0;
	cars_in_queue.reserve(1);
	washed_cars.reserve(1);
	cars_being_washed.reserve(1);
	stage_workers.reserve(1);
}
string Stage::get_id() {return ID;}
vector<Worker*>  Stage::get_workers_list() {return stage_workers;}
void Stage::Add_Worker(Worker* worker) {stage_workers.push_back(worker);}
void Stage::car_in(Car *c) {cars_being_washed.push_back(c);}
void Stage::car_in_queue(Car *c) {cars_in_queue.push_back(c);}
void Stage::car_go_out_stage(Car *car)
{
	for(int i=0 ; i<cars_being_washed.size() ; i++)
	{
		if(cars_being_washed[i] == car)
		{
			cars_being_washed.erase(cars_being_washed.begin() + i);
			washed_cars.push_back(car);
			income += price;
			break;
		}
	}
}
void Stage::car_go_out_line(Car *car)
{
	for(int i=0 ; i<cars_in_queue.size() ; i++)
	{
		if(cars_in_queue[i] == car)
		{
			cars_in_queue.erase(cars_in_queue.begin() + i);
			cars_being_washed.push_back(car);
			break;
		}
	}
}
void Stage::sort_worker()
{
	Worker *temp_address;
	for(int i = 0 ; i<stage_workers.size() ; i++)
	{
		for(int j=0 ; j<stage_workers.size() - 1 ; j++)
		{
			if(stage_workers[j+1]->get_time_to_finish() < stage_workers[j]->get_time_to_finish())
			{
				
				temp_address = stage_workers[j];
				stage_workers[j] = stage_workers[j+ 1];
				stage_workers[j + 1] = temp_address;
			}
		}
	}
}
void Stage::get_report()
{
	cout << "Number of washed cars: " << washed_cars.size() << endl;
	cout << "Number of cars in queue: " << cars_in_queue.size() << endl;
	cout << "Number of cars being washed: " << cars_being_washed.size() << endl;
	cout << "Income: " << income << endl;
}

