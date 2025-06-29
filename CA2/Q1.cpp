#include <iostream>
#include <cmath>

using namespace std;


const int NUM_RANGE = 15;

int num_of_one(long int num, int one_number);
long int min(long int num);
long int max(long int num);
int count(long int num);


int main()
{
    long int num;
    cin >> num;

    int one_number = 0;

    cout << num_of_one(num ,one_number) << endl;
    return 0;
}

int num_of_one(long int num,int one_number)
{
    if(num <= 0)
    {
        return one_number;
    }
    if(abs(num - min(num)) <= abs(num -  max(num)))
    {
        one_number+= count(min(num));
        return  num_of_one(abs(num - min(num)),one_number);
    }
    else if(abs(num - min(num)) > abs(num - max(num)));
    {
        one_number+= count(max(num));
        return  num_of_one(abs(num - max(num)),one_number);
    }
}

long int min(long int num)
{
    long int x = 1;
    for(int i = 0; i < NUM_RANGE - 1; i++)
    {
        if( x <= num  && num< x * 10 + 1)
            return  x;
        x = x* 10 + 1;
    }
    return 0 ;
}

long int max(long int num)
{
    long int x = 1;
    for(int i=0; i < NUM_RANGE - 1; i++)
    {
        if( x <= num  && num <  x * 10 + 1)
            return  x * 10 + 1;
        x = x* 10 + 1;
    }
    return 0 ;

}

int count(long int num)
{
    int counter=0;
    while(num!=0)
    {
        num = num/10;
        counter ++;
    }
    return counter;
}