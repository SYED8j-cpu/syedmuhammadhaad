// Task 10(CP): Convert a number [1-99] to English text
#include <iostream>
#include <string>
using namespace std;

// Function Prototype
string numberToText(int number);

int main()
{
    int number;

    cout << "Enter a number (1-99): ";
    cin >> number;

    cout << numberToText(number) << endl;

    return 0;
}

// Function Definition
string numberToText(int number)
{
    // Arrays for ones and tens place words
    string ones[] = {"", "One", "Two", "Three", "Four", "Five",
                     "Six", "Seven", "Eight", "Nine", "Ten",
                     "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
                     "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    string tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty",
                     "Sixty", "Seventy", "Eighty", "Ninety"};

    if (number < 20)
    {
        // 1-19: directly from ones array
        return ones[number];
    }
    else
    {
        int tensDigit = number / 10; // e.g., 42 -> 4
        int onesDigit = number % 10; // e.g., 42 -> 2

        // Combine tens and ones words (e.g., "Forty" + "Two" = "FortyTwo")
        return tens[tensDigit] + ones[onesDigit];
    }
}