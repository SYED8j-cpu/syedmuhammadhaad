#include <iostream>
using namespace std;

int totalDigits(int num)
{
    int count = 0;

    if (num == 0)
    {
        return 1;
    }

    if (num < 0)
    {
        num = -num;
    }
    while (num > 0)
    {
        num = num / 10;
        count++;
    }

    return count;
}

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;

    int result = totalDigits(number);
    cout << "Total number of digits: " << result << endl;

    return 0;
}
