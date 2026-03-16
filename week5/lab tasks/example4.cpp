#include <iostream>
using namespace std;
int main()
{
    int n, count = 0;
    cout << "enter number:";
    cin >> n;
    for (int i = n; i > 0; i = i / 10)
    {
        count = count + 1;
    }
    cout << "total number of digits:" << count;
    return 0;
}