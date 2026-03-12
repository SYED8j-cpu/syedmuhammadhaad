#include <iostream>
using namespace std;

int main()
{
    string name1, name2, name3;
    int age1, age2, age3;
    cout << "Enter name and age of first brother: ";
    cin >> name1 >> age1;
    cout << "Enter name and age of second brother: ";
    cin >> name2 >> age2;
    cout << "Enter name and age of third brother: ";
    cin >> name3 >> age3;
    if (age1 < age2 && age1 < age3)
    {
        cout << "The youngest brother is: " << name1 << endl;
    }
   else if (age2 < age1 && age2 < age3)
    {
        cout << "The youngest brother is: " << name2 << endl;
    }
    else
    {
        cout << "The youngest brother is: " << name3 << endl;
    }
}
