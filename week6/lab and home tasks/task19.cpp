#include<iostream>
using namespace std;

int main()
{
    int num_elements,largest,smallest;
    cout<<"Enter number of elements: ";cin>>num_elements;
    int array[num_elements];
    cout<<"Enter "<<num_elements<<" numbers: \n";
    cin>>array[0];
    largest=array[0];
    smallest=array[0];
    for (int idx=1;idx<num_elements;idx++)
    {
        cin>>array[idx];
        if (array[idx]>largest)
        {
            largest=array[idx];
        }
        if (array[idx]<smallest)
        {
            smallest=array[idx];
        }
    }
    cout<<"largest number: "<<largest<<endl;
    cout<<"smallest number: "<<smallest<<endl;
    return 0;
}