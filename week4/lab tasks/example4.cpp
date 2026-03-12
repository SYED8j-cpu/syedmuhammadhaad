# include <iostream>
using namespace std;
int main()
{
    int cost;
    cout<<"enter the cost of dress:";
    cin>>cost;
    if(cost > 1500){
        cout<<"buy the dress";
    }
    if(cost < 1500){
        cout<<"do not buy the dress";
    }
}