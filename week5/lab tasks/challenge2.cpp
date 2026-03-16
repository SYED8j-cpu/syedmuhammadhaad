#include <iostream>
using namespace std;

int main()
{
    long long number;
    int digit, count = 0;

    cout << "Enter a number: ";
    cin >> number;
    cout << "Enter the digit to count: ";
    cin >> digit;
    long long temp = number;
    if (temp < 0)
        temp = -temp;

    while (temp > 0)
    {
        int lastDigit = temp % 10;
        if (lastDigit == digit)
        {
            count++;
        }
        temp = temp / 10;
    }

    cout << "The digit " << digit << " appears " << count << " times.";

    return 0;
}
