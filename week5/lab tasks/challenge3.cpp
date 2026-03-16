#include <iostream>
using namespace std;
int gcdSubtraction(int a, int b)
{
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}
int gcdModulo(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int num1, num2;

    cout << "Enter two positive integers: ";
    cin >> num1 >> num2;
    int hcf1 = gcdSubtraction(num1, num2);
    int hcf2 = gcdModulo(num1, num2);
    long long lcm = (1LL * num1 * num2) / hcf2;

    cout << "\n--- Results ---" << endl;
    cout << "GCD (Subtraction Method): " << hcf1 << endl;
    cout << "GCD (Modulo Method): " << hcf2 << endl;
    cout << "LCM: " << lcm << endl;

    return 0;
}
