#include<iostream>
using namespace std;

int main()
{
    int n,largest=0;
    cout<<"Enter number of elements: ";
    cin>>n;
    int array[n];
    cout<<"Enter "<<n<<" numbers, one per line:"<<endl;
    for (int i=0;i<n;i++)
    {
        cin>>array[i];
        if(array[i]>largest)
        {
            largest=array[i];
        }
    } 
    cout<<"Largest number entered is: "<<largest;
    return 0;
}