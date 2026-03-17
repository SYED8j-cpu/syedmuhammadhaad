#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int N;
    double X, P;

    cin >> N >> X >> P;

    double savedMoney = 0.0;
    double currentGiftAmount = 10.0;
    int toyCount = 0;

    for (int age = 1; age <= N; age++)
    {
        if (age % 2 != 0)
        {

            toyCount++;
        }
        else
        {

            savedMoney += (currentGiftAmount - 1.0);

            currentGiftAmount += 10.0;
        }
    }

    savedMoney += (toyCount * P);

    cout << fixed << setprecision(2);

    if (savedMoney >= X)
    {
        cout << "Yes! " << (savedMoney - X) << endl;
    }
    else
    {
        cout << "No! " << (X - savedMoney) << endl;
    }

    return 0;
}
