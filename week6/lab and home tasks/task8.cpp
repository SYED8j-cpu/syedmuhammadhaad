#include<iostream>
using namespace std;

int main()
{
    float sum=0;
    int n;
    cout<<"Enter number of resistors in series: ";
    cin>>n;
    float array[n];
    cout<<"Enter resistence values (in ohms) for "<<n<<" resistors, one per line:"<<endl;
    for (int i=0;i<n;i++)
    {
        cin>>array[i];
        sum+=array[i];
    } 
    cout<<"The total resistence of series circuit is: "<<sum;
    return 0;
}