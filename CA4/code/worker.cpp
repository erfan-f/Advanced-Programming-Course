#include "worker.h"

Worker::Worker(string i , string s , int t)
{
	ID = i;
	stage_id = s;
	Time_to_finish = t;
	free = true;
	car_id = "";
	finish_time = 0;
}
string Worker::get_id() {return ID;}

int Worker::get_time_to_finish() {return Time_to_finish;}

void Worker::free_worker() 
{
	free = true;
	car_id = "";
}
void Worker::apply_car(string id , int time)
{
	free = false;
	car_id = id;
	finish_time = time + Time_to_finish;
}

bool Worker::is_free()
{
	if(free)
		return true;
	return false;
}
bool Worker::is_finish(int time)
{
	if(time == finish_time)
		return true;
	return false;
}
void Worker::get_report()
{
	if(free)
		cout << Worker_status_1 << endl;
	else
		cout << Worker_status_2 << ": " << car_id << endl;
}

