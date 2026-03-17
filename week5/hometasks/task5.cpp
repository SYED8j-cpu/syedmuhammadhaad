#include <iostream>
using namespace std;
void displayFibonacci(int n)
{
    int t1 = 0, t2 = 1, nextTerm;

    cout << "Fibonacci Series: ";
    if (n <= 0)
    {
        cout << "No series to display for " << n << " terms." << endl;
        return;
    }
    else if (n == 1)
    {
        cout << t1 << endl;
        return;
    }
    else
    {
        cout << t1 << ", " << t2 << ", ";
    }
    for (int i = 3; i <= n; ++i)
    {
        nextTerm = t1 + t2;
        cout << nextTerm << ", ";
        t1 = t2;
        t2 = nextTerm;
    }

    cout << endl;
}

int main()
{
    int numberOfTerms;
    cout << "Enter the length of Fibonacci series (number of terms): ";
    cin >> numberOfTerms;
    displayFibonacci(numberOfTerms);

    return 0;
}
