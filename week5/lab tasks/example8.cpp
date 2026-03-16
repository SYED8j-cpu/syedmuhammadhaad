#include <iostream>
#include <iostream>
using namespace std;
int main()
{
    int i = 1, sum = 0;
    while (i <= 5)
    {
        sum = sum + i;
        i = i + 1;
    }
    cout << sum << endl;
}