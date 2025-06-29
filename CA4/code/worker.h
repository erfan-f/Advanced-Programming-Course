#include <iostream>
#include <string>

using namespace std;


const string Worker_status_1 = "Idle"; 
const string Worker_status_2 = "Working"; 

class Worker
{
private:
	string ID;
	string stage_id;
	int Time_to_finish;
	bool free;
	string car_id;
	int finish_time;
public:
	Worker(string i , string s , int t);
	string get_id();
	int get_time_to_finish();
	void free_worker();
	void apply_car(string id , int time);
	bool is_free();
	bool is_finish(int time);
	void get_report();
};
