#include <iostream>
using namespace std;
int main()
{
    int numbers[5];
    cout << "enter 1 number:";
    cin >> numbers[0];
    cout << "enter 2 number:";
    cin >> numbers[1];
    cout << "enter 3 number:";
    cin >> numbers[2];
    cout << "enter 4 number:";
    cin >> numbers[3];
    cout << "enter 5 number:";
    cin >> numbers[4];

    cout << "the first element in array is:" << numbers[0] << endl;
    cout << "the last element in array is:" << numbers[4] << endl;
}