#include<iostream>
using namespace std;

int main()
{
    int num_elements,even=0;
    cout<<"Enter number of elements: ";cin>>num_elements;
    int array[num_elements];
    cout<<"Enter "<<num_elements<<" numbers: ";
    for (int idx=0;idx<num_elements;idx++)
    {
        cin>>array[idx];
        if (array[idx]%2==0)
        {
            even+=1;
        }
        
    }
    cout<<"Total even numbers: "<<even;
    return 0;
}