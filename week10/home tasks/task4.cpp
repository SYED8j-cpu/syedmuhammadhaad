// Task 04 (CP): Project Time Calculator
// Working days = days * 0.9  (10% are training days)
// Hours per worker per day = 8 + 2 = 10 (normal + overtime)
// Total available hours = workingDays * workers * 10
// Round down to nearest integer

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string projectTimeCalculation(int neededHours, int days, int workers) {
    // 10% of days are training days → only 90% are working days
    double workingDays = days * 0.9;

    // Each worker works 10 hours/day (8 normal + 2 overtime)
    double totalHours = workingDays * workers * 10;

    // Round down to nearest integer
    int availableHours = (int)floor(totalHours);

    if (availableHours >= neededHours) {
        int hoursLeft = availableHours - neededHours;
        return "Yes!" + to_string(hoursLeft) + " hours left.";
    } else {
        int hoursNeeded = neededHours - availableHours;
        return "Not enough time!" + to_string(hoursNeeded) + " hours needed.";
    }
}

int main() {
    int neededHours, days, workers;

    cout << "Enter needed hours: ";
    cin >> neededHours;

    cout << "Enter number of days of firm: ";
    cin >> days;

    cout << "Enter number of workers: ";
    cin >> workers;

    cout << projectTimeCalculation(neededHours, days, workers) << endl;

    return 0;
}