#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const vector<int> delta_move = {1,-1};

void get_input(vector<vector<int>> &metro_station,vector<pair<int,int>> &history, pair <int,int> &source,pair <int,int> &dest);
vector<int> time_travel(vector<vector<int>> metro_station, vector<pair<int,int>> &history, vector<int> &min_time,pair <int,int> source,pair <int,int> dest ,int &move_in_line , int &move_out_line);
int check_station(vector<vector<int>> metro_station , pair<int,int> source);
int check_history(vector<pair<int,int>> history ,pair <int,int> source);


int main()
{
	vector<vector<int>>  metro_station;
	pair <int,int> source,dest;
	vector<int> min_time;
	

	vector<pair<int,int>> history;

	int move_in_line = 0;
	int move_out_line = 0; 

	get_input(metro_station,history,source,dest);

	min_time = time_travel(metro_station,history,min_time,source,dest,move_in_line,move_out_line);

	int min = min_time[0];

	for(int i = 0 ; i<min_time.size() ; i++)
	{
		if(min_time[i] < min)
			min = min_time[i];
	}

	cout << min << endl;

	return 0;
}

void get_input(vector<vector<int>> &metro_station,vector<pair<int,int>> &history , pair <int,int> &source,pair <int,int> &dest)
{
	int n;
	int m;

	cin >> n;

	for(int i=0 ; i<n ; i++)
	{
		metro_station.push_back({});
		cin >> m;
		for(int j=0;j<m;j++)
		{
			metro_station[i].push_back(0);
			cin >>metro_station[i][j] ;
		}
	}
	cin >> source.first >> source.second >> dest.first >> dest.second; 
	history.push_back(source);
}


vector<int> time_travel(vector<vector<int>> metro_station, vector<pair<int,int>> &history, vector<int> &min_time,pair <int,int> source,pair <int,int> dest ,int &move_in_line , int &move_out_line)
{
	if(source.first == dest.first && source.second == dest.second)
	{
		min_time.push_back(move_in_line * 1 + move_out_line * 2);
		return min_time;
	}

	for(int i =0 ; i<3 ; i++)
	{
		
		if(i==2 && metro_station[source.first - 1][source.second - 1] != 0)
		{
			pair<int,int> new_source;
			new_source.first = metro_station[source.first - 1][source.second - 1] ;
			new_source.second = check_station(metro_station,source) + 1 ;

			if(check_history(history,new_source) == 1) 
			{
				new_source.first = source.first;
				new_source.second = source.second;
				continue;
			}

			history.push_back(new_source);

			move_out_line ++ ;
			time_travel(metro_station,history,min_time,new_source,dest,move_in_line,move_out_line);
			move_out_line -- ;
			history.pop_back();
		}
		else if (i==0 || i== 1)
		{
			pair<int,int> new_source;
			new_source.first = source.first;
			new_source.second = source.second + delta_move[i];
			if(new_source.second <=0 || new_source.second > metro_station[source.first - 1].size())
			{
				continue;
			}

			if(check_history(history,new_source) == 1) 
			{
				new_source.first = source.first;
				new_source.second = source.second;
				continue;
			}

			history.push_back(new_source);
			
			move_in_line ++ ;
			time_travel(metro_station,history,min_time,new_source,dest,move_in_line,move_out_line);
			move_in_line --; 
			history.pop_back();
		}	
	}
	return min_time ;
}

int check_station(vector<vector<int>> metro_station , pair<int,int> source)
{
	for(int i = 0 ; i < metro_station[ metro_station[source.first - 1][source.second - 1] - 1 ].size() ; i++)
	{
		if( metro_station[ metro_station[source.first - 1][source.second - 1] - 1 ][i] == source.first)
			return i;
	}
	return 0;
}

int check_history(vector<pair<int,int>> history ,pair <int,int> source)
{
	for(int i=0 ; i<history.size() ; i++)
	{
		if(history[i] == source)
			return 1;
	}
	return 0;
}