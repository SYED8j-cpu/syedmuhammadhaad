// Task 06(CP): checkAlphabet - returns string based on 'A' or 'a'
#include <iostream>
#include <string>
using namespace std;
 
// Function Prototype
string checkAlphabet(char ch);
 
int main()
{
    char ch;
 
    cout << "Enter a character (A/a): ";
    cin >> ch;
 
    cout << checkAlphabet(ch) << endl;
 
    return 0;
}
 
// Function Definition
string checkAlphabet(char ch)
{
    if (ch == 'A')
        return "You have entered Capital A";
    else
        return "You have entered small a";
}