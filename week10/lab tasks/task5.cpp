// Task 05(CP): Solve quadratic equation ax^2 + bx + c = 0
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, c;

    cout << "Enter the value of a: ";
    cin >> a;

    cout << "Enter the value of b: ";
    cin >> b;

    cout << "Enter the value of c: ";
    cin >> c;

    double discriminant = (b * b) - (4 * a * c);

    if (discriminant > 0)
    {
        // Two real and distinct roots
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Solutions: x = " << root1 << " and x = " << root2 << endl;
    }
    else if (discriminant == 0)
    {
        // One real (repeated) root
        double root = -b / (2 * a);
        cout << "Solution: x = " << root << endl;
    }
    else
    {
        // Two complex roots
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Complex Solutions: x = " << realPart << " + "
             << imaginaryPart << "i and x = " << realPart
             << " - " << imaginaryPart << "i" << endl;
    }

    return 0;
}