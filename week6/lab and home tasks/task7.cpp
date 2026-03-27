#include<iostream>
using namespace std;
int main()
{
    string word;
    cout<<"Enter a word: ";
    cin>>word;
    cout<<"shifted word: ";
    for (int i = 0; word[i] != '\0'; i++)
    {
        cout << char(word[i] + 1);
    }
    return 0;
}