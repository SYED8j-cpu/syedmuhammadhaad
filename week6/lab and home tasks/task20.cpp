#include<iostream>
using namespace std;

int main()
{
    string array[5];
    cout<<"Enter names of 5 students: \n";
    for (int idx=0;idx<5;idx++)
    {
        cin>>array[idx];
    }
    cout<<"Student names are: \n";
    for(int i=0;i<5;i++)
    {
        cout<<"Student "<<i+1<<": "<<array[i]<<endl;
    }
    return 0;
}