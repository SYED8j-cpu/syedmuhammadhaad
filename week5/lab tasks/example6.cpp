#include <iostream>
using namespace std;
int main()
{
    int value;
    cout << "please enter a positive number:";
    cin >> value;
    while (value <= 0)
    {
        cout << "error:" << value << "is not a positive number." << endl;
        cin >> value;
    }
    cout << "program ends" << endl;
}