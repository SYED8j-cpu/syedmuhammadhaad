# include <iostream>
using namespace std;
int main()
{
    int number1,number2;
    cout<<"please enter the first number:";
    cin>>number1;
    cout<<"please enter the second number:";
    cin>>number2;
    if( number1<number2 ){
        cout<< "number"<< number2<<"is greater than"<<number1;
    }
    else{
        cout<<"number"<< number1 <<"is greater than"<<number2;
    }
}