#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void get_available_unit(vector<vector<string>> &unit , int m);
void get_previous_unit(vector<vector<string>> &unit , int n);
void get_required_unit(vector<string> &unit , int k);
float GPA_Calculator(vector<vector<string>> unit , int n);
int check1(vector<vector<string>> unit1 , vector<string> unit3 , int m,int k ,float GPA);
int check2(vector<vector<string>> unit1 , vector<vector<string>> unit2 ,vector<string> unit3 , int m, int n,int k);



int main()
{
    int m,n,k;

    cin >> m;
    vector<vector<string>> available_unit (m,vector<string>(3));
    get_available_unit(available_unit,m);

    cin >> n;
    vector<vector<string>> previous_unit (n,vector<string>(3));
    get_previous_unit(previous_unit,n);

    float GPA = GPA_Calculator(previous_unit,n);

    cin >> k;
    vector<string> required_unit(k);
    get_required_unit(required_unit,k);

    int  check = check1(available_unit,required_unit,m,k,GPA);

    if(check == 1) 
    {
        cout << "Course Not Offered!" << endl;
        return 0;
    }
    else if(check == 2) 
    {
        cout << "Maximum Units Validation Failed!" << endl; 
        return 0;
    }
    else if(check == 3) 
    {
        cout << "Minimum Units Validation Failed!" << endl; 
        return 0;
    }

    int next_check = check2(available_unit,previous_unit,required_unit,m,n,k);
    if(next_check == 1) 
    {
        cout << "Course Already Taken!" << endl;
        return 0;
    }
    else if(next_check == 2) 
    {
        cout << "Prerequisites Not Met!" << endl; 
        return 0;
    }
    cout << "Ok!" << endl;
    return 0;
}

void get_available_unit(vector<vector<string>> &unit , int m)
{
    for(int i=0 ; i<m;i++)
    {   
        cin >> unit[i][0] >> unit[i][1] >> unit[i][2];
    }
}

void get_previous_unit(vector<vector<string>> &unit , int n)
{
    for(int i=0 ; i<n ; i++)
    {
        cin >> unit[i][0] >> unit[i][1] >> unit[i][2];
    }
}

void get_required_unit(vector<string> &unit , int k)
{

    for(int i=0 ;i <k ; i++) cin >> unit[i];
}

float GPA_Calculator(vector<vector<string>> unit , int n)
{
    float sum =0;
    int num_unit = 0;

    for(int i=0; i<n ;i++)
    {
        sum += (stof(unit[i][2]) * stoi(unit[i][1]));
        num_unit += stoi(unit[i][1]);
    }

    return sum/num_unit;
}

int check1(vector<vector<string>> unit1 , vector<string> unit3 , int m,int k ,float GPA)
{

    int max , min = 12;
    if(GPA >=17) max = 24;
    else if(GPA >=12) max = 20;
    else max = 14;

    int num_unit = 0;
    int flag;
    for(int i=0 ; i<k ; i++)
    {
        flag =0;
        for(int j=0 ; j<m ;j++)
        {
            if(unit3[i] == unit1[j][0]) 
            {
                flag = 1;
                num_unit += stoi(unit1[j][1]);
                break;
            }
        }
        if(flag == 0) 
        {
            return 1;
        }
    }
    if(num_unit > max) return 2;
    else if(num_unit < min) return 3;

    return 0;

}
int check2(vector<vector<string>> unit1 , vector<vector<string>> unit2 ,vector<string> unit3 , int m, int n,int k)
{

    vector<string> Pre_requisites;
    string temp;
    int size;
    int flag;

    for(int i=0 ; i<k;i++)
    {
        size = 0;
        for(int j=0 ;j<m ;j++)
        {
            if(unit3[i] == unit1[j][0]) 
            {
                for(int l=0 ; l<n ; l++)
                {
                    if(unit3[i] == unit2[l][0]  && stof(unit2[l][2]) > 10) 
                    {
                        return 1;
                    }
                }
                stringstream s(unit1[j][2]);
                while(getline(s,temp,','))
                {
                    Pre_requisites.push_back(temp);
                    size++;
                }
                for(int r=0; r<size ;r++)
                {
                    flag = 0;
                    for(int g=0;g<n;g++)
                    {
                        if(unit2[g][0] == Pre_requisites[r])
                        {
                            if(stof(unit2[g][2]) >= 10)  flag =1;
                        }
                    }
                    if(flag == 0) return 2;
                }
                Pre_requisites.clear();
            }
        }
    }
    return 0;   
}
