#include <iostream>
using namespace std;

int main()
{
    int count = 1;

    for (int i = 1; i <= 3; i++)
    {

        for (int j = 1; j <= 3; j++)
        {
            cout << count << " ";
            count++;
        }

        cout << endl;
    }

    return 0;
}
