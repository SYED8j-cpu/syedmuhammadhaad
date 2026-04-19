#include<iostream>
using namespace std;

int main()
{
    int num_customer;
    cout<<"Enter number of customers: ";cin>>num_customer;
    string array[num_customer];
    cout<<"Enter names of "<<num_customer<<" customers: ";
    for (int idx=0;idx<num_customer;idx++)
    {
        cin>>array[idx];    
    }
    char alphabet;
    int count=0;
    cout<<"Enter the letter to check: ";cin>>alphabet;
    for(int i=0;i<num_customer;i++)
    {
        if(array[i][0]==alphabet)
        {
            count+=1;
        }
    }
    cout<<"Total names starting with '"<<alphabet<<" : "<<count;
    return 0;
}