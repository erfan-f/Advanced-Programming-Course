#include <fstream>
#include <sstream>
#include "stage.h"

using namespace std;

const int Time_Source = 0;
const char Seprator = ',';



class Car_Wash
{
private:
	int time = Time_Source;
	vector<Worker *> workers;
	vector<Stage *> stages;
	vector<Car *> cars;
public:
	void read_from_files(string stage_path , string workers_path);
	void read_stages(string path);
	void read_workers(string path);
	void Add_Stage(string ID , float Price);
	void Add_Worker(string ID , string stage_id , int Time_to_finish);
	void Add_Car(vector<string> stages_id );
	void get_stage_status(string stage_id);
	void get_worker_status(string worker_id);
	void get_car_status(string car_id);
	Car* find_car(string car_id);
	Stage* find_stage(string stage_id);
	Worker* find_worker(string worker_id);
	bool is_worker_found(Stage *stage , string car_id);
	Worker* found_worker(Stage *stage , string car_id);
	void through_time(int dt);
	void check_operation();	
	void apply_stage(string car_id , string car_status);
	void arrived_report(string car_id);
	void queue_to_stage_report(string car_id);
	void stage_to_stage_report(string car_id);
};
