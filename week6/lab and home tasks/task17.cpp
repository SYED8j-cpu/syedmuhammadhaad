#include<iostream>
using namespace std;
void sum(int arr[],int size)
{
    int sum = 0;
    for (int j=0;j<size;j++)
    {
        sum+=arr[j];
    }
    cout<<"Sum of all elements: "<<sum;
}
int main()
{
    int i;
    cout<<"Enter number of elements: ";cin>>i;
    int array[i];
    cout<<"Enter "<<i<<" numbers: ";
    for (int idx=0;idx<i;idx++)
    {
        cin>>array[idx];
    }
    sum(array,i);
    return 0;
}