#include <iostream>
#include <vector>
#include <string>



using namespace std;

int main()
{
	int m,n;
	cin >> n >> m;
	
	vector<vector<string>>   train(n, vector<string>(5));
	
	for(int i=0; i<n ; i++)
	{
			cin >> train[i][0] >> train[i][1] >> train[i][2]  >> train[i][3]  >> train[i][4];
					
	}
	
	string source , destination , time;
	int  count;
	
	for(int j=0 ; j<m ; j++)
	{
		cin >> source >> destination >> time >> count ;
		for(int i=0 ; i<n;i++)
		{
			if(source == train[i][1])
				if(destination == train[i][2])
						if( time <= train[i][3])	
							if(count <= stoi(train[i][4]))
							{
							cout << train[i][0] <<"  " <<train[i][3] << "  "<< train[i][4] << endl; 														
							}			
		}
		cout << "----------" << endl;	
	}
	
	return 0;
}


