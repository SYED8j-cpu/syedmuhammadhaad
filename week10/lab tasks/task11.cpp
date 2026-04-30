// Task 11(CP): calculatePoolState - determines pool fill or overflow
#include <iostream>
#include <string>
using namespace std;
 
// Function Prototype
string calculatePoolState(int V, int P1, int P2, float H);
 
int main()
{
    int V, P1, P2;
    float H;
 
    cout << "Enter volume of the pool in liters: ";
    cin >> V;
 
    cout << "Enter flow rate of the first pipe per hour: ";
    cin >> P1;
 
    cout << "Enter flow rate of the second pipe per hour: ";
    cin >> P2;
 
    cout << "Enter hours that the worker is absent: ";
    cin >> H;
 
    cout << calculatePoolState(V, P1, P2, H) << endl;
 
    return 0;
}
 
// Function Definition
string calculatePoolState(int V, int P1, int P2, float H)
{
    // Total water filled by both pipes
    float totalWater = (P1 + P2) * H;
 
    if (totalWater <= V)
    {
        // Pool is not overflowing — calculate percentages
        int poolPercent  = (int)(totalWater / V * 100);          // truncate (no rounding)
        int pipe1Percent = (int)((P1 * H) / totalWater * 100);   // truncate
        int pipe2Percent = (int)((P2 * H) / totalWater * 100);   // truncate
 
        return "The pool is " + to_string(poolPercent) +
               "% full. Pipe 1: " + to_string(pipe1Percent) +
               "%. Pipe 2: " + to_string(pipe2Percent) + "%.";
    }
    else
    {
        // Pool overflows
        float overflow = totalWater - V;
 
        // Format H nicely: show as integer if it has no decimal part
        string hoursStr;
        if (H == (int)H)
            hoursStr = to_string((int)H);
        else
        {
            // Keep one decimal place for float hours
            hoursStr = to_string(H);
            // Trim trailing zeros after decimal
            hoursStr = hoursStr.substr(0, hoursStr.find('.') + 2);
        }
 
        // Format overflow: remove trailing zeros
        string overflowStr;
        if (overflow == (int)overflow)
            overflowStr = to_string((int)overflow);
        else
        {
            overflowStr = to_string(overflow);
            overflowStr = overflowStr.substr(0, overflowStr.find('.') + 2);
        }
 
        return "For " + hoursStr + " hours, the pool overflows with " +
               overflowStr + " liters.";
    }
}
 