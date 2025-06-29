#include "car.h"


Car::Car(string i, string s, vector<string> st)
{
	ID = i;
	status = s;
	stages = st;
	current_stage_id = st[0];
	Worker w("","",0);
	current_Worker = &w;
	pass_stages.reserve(1);		
}

string Car::get_id() {return ID;}
string Car::get_status() {return status;}
vector<string> Car::get_stages() {return stages;}
string Car::get_current_stage_id() {return current_stage_id;}
vector<string> Car::get_pass_stages() {return pass_stages;}

void Car::change_status(string s) { status = s;}
void Car::change_worker(Worker *w) {current_Worker = w;}
string Car::get_previous_stage() {return pass_stages.back();}
bool Car::is_in_service()
{
	if(status == Car_Status_2)
		return true;
	return false;
}
bool Car::is_in_line()
{
	if(status == Car_Status_1)
		return true;
	return false;
}
bool Car::is_pass(int time)
{
	if(current_Worker->is_finish(time))
	{	
		return true;
	}
	return false; 
}
bool Car::is_done()
{
	if(pass_stages.size() == stages.size())
		return true;
	return false;
}
void Car::out_from_stage()
{
	current_Worker->free_worker();
	pass_stages.push_back(current_stage_id);
	if(pass_stages.size() != stages.size())
		current_stage_id = stages[pass_stages.size()];
	else
	{
		current_stage_id = "";
		status = Car_Status_3;
	}
}
void Car::get_report()
{
	if(status == Car_Status_3)
		cout << status << endl;
	else
		cout << status << ": " << current_stage_id << endl;
}