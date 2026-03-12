#include <iostream>
using namespace std;
int main()
{
    int temp1, temp2;
    cout << "enter temperature of city 1:";
    cin >> temp1;
    cout << "enter temperature of city 2:";
    cin >> temp2;
    int difference = temp1 - temp2;
    if (difference > 10)
    {
        cout << "The difference is too big" << endl;
    }
    else
    {
        cout << "program ends" << endl;
    }
}