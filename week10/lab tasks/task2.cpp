// Task 02(OP): Power of a number using pow()
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double base, exponent;

    cout << "Enter the base number: ";
    cin >> base;

    cout << "Enter the exponent: ";
    cin >> exponent;

    cout << base << " raised to the power " << exponent
         << " is: " << pow(base, exponent) << endl;

    return 0;
}
