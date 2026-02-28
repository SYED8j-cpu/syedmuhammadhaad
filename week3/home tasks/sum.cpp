# include <iostream>
using namespace std;
int main()
{
cout<<"enter a 4-digit number:"<<endl;
int number;
cin>>number;
int digit1,digit2,digit3,digit4,sum;
digit1 = number % 10;

digit2 = number % 10;
number = number / 10;

digit3 = number % 10;
number = number/10;

digit4 = number % 10;
number = number / 10;

sum=digit1+digit2+digit3+digit4;
cout<<"sum of the individual digits:"<<sum<<endl;
}