#include <vector>
#include "worker.h"

using namespace std;


const string Primary_situation = "Arrived";
const string Car_Status_1 = "In line";
const string Car_Status_2 = "In service";
const string Car_Status_3 = "Done";

class Car
{
private:
	string ID;
	string status;
	vector<string> stages;
	vector<string> pass_stages;
	string current_stage_id;
	Worker* current_Worker;

public:
	Car(string i, string s, vector<string> st);
	string get_id();
	string get_status();
	vector<string> get_stages();
	string get_current_stage_id();
	vector<string> get_pass_stages(); 
	void change_status(string s); 
	void change_worker(Worker *w);
	string get_previous_stage();
	bool is_in_service();
	bool is_in_line();
	bool is_pass(int time);
	bool is_done();
	void out_from_stage();
	void get_report();
};