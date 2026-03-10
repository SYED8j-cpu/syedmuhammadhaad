# include <iostream>
using namespace std;
int main()
{
    int number,even;
    cout<<"please enter the number:";
    cin>>number;
    even = number%2;
    if(even == 0){
        cout<<"the number is even";
    }
    else{
        cout<<"the number is odd";
    }
}