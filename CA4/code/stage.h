#include "car.h"

using namespace std;


class Stage
{
private:
	string ID;
	float price;
	vector<Car*> cars_in_queue;
	vector<Car*> washed_cars;
	vector<Car*> cars_being_washed;
	vector<Worker*> stage_workers;
	float income;

public:
	Stage(string i , float p);
	string get_id();
	vector<Worker*>  get_workers_list();
	void Add_Worker(Worker* worker);
	void car_in(Car *c);
	void car_in_queue(Car *c);
	void car_go_out_stage(Car *car);
	void car_go_out_line(Car *car);
	void sort_worker();
	void get_report();
};