#include <iostream>
using namespace std;

int main() {
    int n1, n2, a, b, temp, gcd, lcm;

    cout << "Enter two numbers: ";
    cin >> n1 >> n2;
    a = n1;
    b = n2;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    gcd = a;
    lcm = (n1 * n2) / gcd;

    cout << "GCD: " << gcd << endl;
    cout << "LCM: " << lcm << endl;

    return 0;
}
