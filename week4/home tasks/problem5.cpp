#include <iostream>
using namespace std;

int main()
{
    int holidays;
    cout << "Enter number of holidays: ";
    cin >> holidays;
    int totalDays = 365;
    int norm = 30000;
    int workingDays = totalDays - holidays;
    int totalPlayTime = (workingDays * 63) + (holidays * 127);
    int difference = norm - totalPlayTime;
    if (difference >= 0)
    {
        cout << "Tom sleeps well" << endl;

        int hours = difference / 60;
        int minutes = difference % 60;
        cout << hours << " hours and " << minutes << " minutes less for play" << endl;
    }
    else
    {
        cout << "Tom will run away" << endl;
        int absDifference = -difference;
        int hours = absDifference / 60;
        int minutes = absDifference % 60;
        cout << hours << " hours and " << minutes << " minutes more for play" << endl;
    }
}
