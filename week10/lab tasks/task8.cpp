// Task 08(CP): OddishOrEvenish - checks if digit sum is odd or even
#include <iostream>
#include <string>
using namespace std;
 
// Function Prototype
string oddishOrEvenish(int number);
 
int main()
{
    int number;
 
    cout << "Enter a five-digit number: ";
    cin >> number;
 
    cout << oddishOrEvenish(number) << endl;
 
    return 0;
}
 
// Function Definition
string oddishOrEvenish(int number)
{
    // Extract all 5 digits and sum them
    int d1 = number / 10000;           // ten-thousands digit
    int d2 = (number / 1000) % 10;     // thousands digit
    int d3 = (number / 100)  % 10;     // hundreds digit
    int d4 = (number / 10)   % 10;     // tens digit
    int d5 = number % 10;              // units digit
 
    int digitSum = d1 + d2 + d3 + d4 + d5;
 
    if (digitSum % 2 != 0)
        return "Oddish";
    else
        return "Evenish";
}