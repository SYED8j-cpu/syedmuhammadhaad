#include<iostream>
using namespace std;

int main()
{
    string str;
    char vowels[10]={'a','e','i','o','u','A','E','I','O','U'};

    cout << "Enter a sentence: ";
    getline(cin, str);

    cout << "Output: ";

    for(int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if(ch!=vowels[0] && ch!=vowels[1] && ch!=vowels[2] && ch!=vowels[3] && ch!=vowels[4] &&
           ch!=vowels[5] && ch!=vowels[6] && ch!=vowels[7] && ch!=vowels[8] && ch!=vowels[9])
        {
            cout << ch;
        }
    }

    return 0;
}