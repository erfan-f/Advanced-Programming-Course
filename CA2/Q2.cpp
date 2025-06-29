#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

void print_tree(vector<pair<string,int>> data ,int dim_limit ,int position ,int current_dim ,vector<int>& pipe , bool first_pipe_status);
void print_first_pipe(bool first_pipe_status);


int main()
{
    int n , dim_limit;

    cin >> n >> dim_limit;

    vector<pair<string,int>> data(n);
    vector<int> root_0;

    vector<int> pipe;
    pipe.push_back(1);

    for(int i = 0 ; i < n ; i++)
    {
        cin >> data[i].first >> data[i].second;
    }

    for(int j = 0 ; j < data.size() ; j++)
    {
        if(data[j].second == 0)
            root_0.push_back(j);
    }
    for(int k = 0 ; k < root_0.size() ; k++)
    {
        if(k == root_0.size() - 1)
            print_tree(data,dim_limit,root_0[k],1,pipe,false);
        else
            print_tree(data,dim_limit,root_0[k],1,pipe,true);
    }
    return 0;
}  


void print_tree(vector<pair<string,int>> data,int dim_limit ,int position ,int current_dim ,vector<int> &pipe , bool first_pipe_status)
{
    bool pipe_flag = false;
    if(current_dim <= dim_limit)
    {
        if(current_dim == 1)
        {
            cout << "|__" << data[position].first << endl;
        }
        else
        {
            if(pipe.size() == 1)
            {
                print_first_pipe(first_pipe_status);
                cout << "  ";
                for(int p = 0 ; p < current_dim - 2 ; p++)
                {
                    cout << "   ";
                }
                cout << "|__" << data[position].first << endl ;
            }
            else 
            {
                if(current_dim > pipe[pipe.size() - 1])
                {
                    print_first_pipe(first_pipe_status);
                    for(int i = 0 ; i < pipe.size() - 1 ; i++)                     
                    {
                        for(int k = 0 ; k < pipe[i+ 1] - pipe[i] - 1 ; k++)
                        {
                            cout << "   ";
                        }
                        cout << "  |";
                    }
                    for(int l = 0 ; l < current_dim - pipe[pipe.size() - 1] -1 ; l++)
                    {
                        cout<< "   ";
                    }
                    cout << "  |__" << data[position].first << endl;
                }
                else
                {
                    print_first_pipe(first_pipe_status);
                    for(int i = 0 ; i < pipe.size() - 2 ; i++)                     
                    {
                        for(int k = 0 ; k < pipe[i+ 1] - pipe[i] - 1 ; k++)
                        {
                            cout << "   ";
                        }
                        cout << "  |";
                    }
                    for(int l = 0 ; l < current_dim - pipe[pipe.size() - 2] -1 ; l++)
                    {
                        cout<< "   ";
                    }
                    cout << "  |__" << data[position].first << endl;
                }
            }
        }   
        
    }
    for(int j = position ; j < data.size() ; j++)
    { 
        
        if(data[j].second - 1 == position)
        {
            for(int g = j + 1 ; g < data.size() ; g++)
            {
                if(data[j].second == data[g].second)
                {
                    pipe.push_back(current_dim + 1);
                    pipe_flag = true;
                    break;
                }
            }
            print_tree(data,dim_limit,j,current_dim + 1,pipe,first_pipe_status);
            if(pipe_flag == true)
                pipe.pop_back();
            pipe_flag = false ;
        }   
    }
}

void print_first_pipe(bool first_pipe_status)
{
    if(first_pipe_status == true)
        cout << "|";
    else
        cout << " ";
}