// Task 07(CP): IsSymmetrical - checks if a 3-digit number equals its reverse
#include <iostream>
using namespace std;
 
// Function Prototype
bool isSymmetrical(int number);
 
int main()
{
    int number;
 
    cout << "Enter a three-digit number: ";
    cin >> number;
 
    if (isSymmetrical(number))
        cout << "The number is symmetrical." << endl;
    else
        cout << "The number is not symmetrical." << endl;
 
    return 0;
}
 
// Function Definition
// For a 3-digit number ABC, it is symmetrical if A == C (first digit == last digit)
bool isSymmetrical(int number)
{
    int firstDigit  = number / 100;       // e.g., 232 -> 2
    int lastDigit   = number % 10;        // e.g., 232 -> 2
 
    return firstDigit == lastDigit;
}