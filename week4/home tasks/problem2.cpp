#include <iostream>
using namespace std;
int main()
{
    int speed;
    cout << "Enter the speed of the car (km/h): ";
    cin >> speed;
    if (speed > 100)
    {
        cout << "Halt....YOU WILL BE CHALLANED!!!" << endl;
    }
    else
    {
        cout << "Perfect! You’re going good." << endl;
    }
}
