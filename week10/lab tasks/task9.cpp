// Task 09(CP): timeTravel - adds 15 minutes to a given time (24-hour format)
#include <iostream>
#include <string>
using namespace std;
 
// Function Prototype
string timeTravel(int hours, int minutes);
 
int main()
{
    int hours, minutes;
 
    cout << "Enter Hours: ";
    cin >> hours;
 
    cout << "Enter Minutes: ";
    cin >> minutes;
 
    cout << timeTravel(hours, minutes) << endl;
 
    return 0;
}
 
// Function Definition
string timeTravel(int hours, int minutes)
{
    // Add 15 minutes
    minutes += 15;
 
    // Handle minute overflow
    if (minutes >= 60)
    {
        minutes -= 60;
        hours += 1;
    }
 
    // Handle hour overflow (24-hour wrap)
    if (hours >= 24)
        hours -= 24;
 
    // Build the result string as "h:mm" (hours not zero-padded, minutes not zero-padded)
    return to_string(hours) + ":" + to_string(minutes);
}
 