#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double inheritance;
    int targetYear;
    int age = 18;

    cout << "Enter the inheritance amount: ";
    cin >> inheritance;
    cout << "Enter the year to live until: ";
    cin >> targetYear;

    for (int year = 1800; year <= targetYear; year++)
    {
        if (year % 2 == 0)
        {

            inheritance -= 12000;
        }
        else
        {

            inheritance -= (12000 + 50 * age);
        }

        age++;
    }

    if (inheritance >= 0)
    {
        cout << "Yes! He will live a carefree life and will have "
             << fixed << setprecision(2) << inheritance << " dollars left." << endl;
    }
    else
    {
        cout << "He will need " << fixed << setprecision(2) << abs(inheritance)
             << " dollars to survive." << endl;
    }

    return 0;
}
