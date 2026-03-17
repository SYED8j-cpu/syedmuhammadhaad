#include <iostream>
using namespace std;
int main()
{
    char choice = 'y';
    while (choice != 'N' &&choice != 'n')
    {
        cout << " i am happy!" << endl;
        cout << "enter your choice:";
        cin >> choice;
    }
}