#include<iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    int array[n];
    cout << "Enter elements:\n";
    for(int i = 0; i < n; i++)
    {
        cin >> array[i];
    }

    bool isSpecial = true;
    for(int i = 0; i < n; i++)
    {
        if(i % 2 == 0)
        {
            if(array[i] % 2 != 0)
            {
                isSpecial = false;
                break;
            }
        }
        else
        {
            if(array[i] % 2 == 0)
            {
                isSpecial = true;
                break;
            }
        }
    }

    if(isSpecial)
        cout << "The array is special.";
    else
        cout << "The array is not special.";

    return 0;
}