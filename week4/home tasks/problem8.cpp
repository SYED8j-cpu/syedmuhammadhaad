#include <iostream>
#include <string>

using namespace std;

int main()
{
    int num;
    cout << "Enter a number (0-100): ";
    cin >> num;
    if (num < 0 || num > 100)
    {
        cout << "Out of range" << endl;
    }
    else if (num == 100)
    {
        cout << "one hundred" << endl;
    }
    else if (num == 0)
    {
        cout << "zero" << endl;
    }
    else
    {
        string ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                         "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

        string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

        if (num < 20)
        {
            cout << ones[num] << endl;
        }
        else
        {
            int tensDigit = num / 10;
            int onesDigit = num % 10;

            if (onesDigit == 0)
            {
                cout << tens[tensDigit] << endl;
            }
            else
            {
                cout << tens[tensDigit] << " " << ones[onesDigit] << endl;
            }
        }
    }
}
