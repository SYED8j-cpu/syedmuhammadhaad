#include <iostream>
using namespace std;

int main()
{
    int i, sum = 0;
    cout << "Enter number of elements: ";
    cin >> i;
    int array[i];
    cout << "Enter " << i << " numbers: ";
    for (int idx = 0; idx < i; idx++)
    {
        cin >> array[idx];
        sum += array[idx];
    }
    cout << "Sum of all elements: " << sum;
    return 0;
}