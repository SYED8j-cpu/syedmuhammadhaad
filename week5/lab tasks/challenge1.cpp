#include <iostream>
using namespace std;

int main()
{
    // Array to store the numbers for which we want the multiplication table
    int numbers[] = {24, 50, 29};
    // The number of elements in the array
    int num_count = sizeof(numbers) / sizeof(numbers[0]);

    // Outer loop to iterate through each number in the array
    for (int j = 0; j < num_count; j++)
    {
        int n = numbers[j];
        cout << "Multiplication table for " << n << ":" << endl;
        cout << "--------------------------" << endl;

        // Inner loop to generate and print the table for the current number (from 1 to 10)
        for (int i = 1; i <= 10; ++i)
        {
            cout << n << " * " << i << " = " << n * i << endl;
        }
        cout << endl; // Add a blank line for readability between tables
    }

    return 0;
}
