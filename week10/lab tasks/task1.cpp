// Task 01(OP): Print minimum of two numbers using min()
#include <iostream>
#include <cmath>
using namespace std;
 
int main()
{
    double number1, number2;
 
    cout << "Enter the first number: ";
    cin >> number1;
 
    cout << "Enter the second number: ";
    cin >> number2;
 
    cout << "The minimum of " << number1 << " and " << number2
         << " is: " << min(number1, number2) << endl;
 
    return 0;
}