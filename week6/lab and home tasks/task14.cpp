#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the number of elements: ";cin>>n;
    if (n <= 0)
    {
        cout<<"Invalid input. Please enter a number greater than 0."<<endl;
    }
    int array[n];
    cout<<"Enter the elements: ";
    for (int i = 0; i < n; i++)
    {
        cin>>array[i];
    }
    cout<<"Numbers in reverse order are: ";
    for (int i = n-1; i >= 0; i--)
    {
        cout<<array[i]<<" ";
    }
    return 0;
}