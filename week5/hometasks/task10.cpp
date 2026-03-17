#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int n;
    cout << "Enter the count of numbers: ";
    cin >> n;
    double c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;

    for (int i = 0; i < n; i++)
    {
        int num;
        cout << "Enter number: ";
        cin >> num;

        if (num < 200)
        {
            c1++;
        }
        else if (num <= 399)
        {
            c2++;
        }
        else if (num <= 599)
        {
            c3++;
        }
        else if (num <= 799)
        {
            c4++;
        }
        else
        {
            c5++;
        }
    }
    cout << fixed << setprecision(2);
    cout << "p1: " << (c1 / n) * 100 << "%" << endl;
    cout << "p2: " << (c2 / n) * 100 << "%" << endl;
    cout << "p3: " << (c3 / n) * 100 << "%" << endl;
    cout << "p4: " << (c4 / n) * 100 << "%" << endl;
    cout << "p5: " << (c5 / n) * 100 << "%" << endl;

    return 0;
}
