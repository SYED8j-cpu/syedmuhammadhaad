#include <iostream>
using namespace std;
int main()
{
    char ch = 'y';
    while (ch == 'y')
    {
        cout << "i am happy" << endl;
        cout << "press y to continue or any key to exit" << endl;
        cin >> ch;
    }
}
