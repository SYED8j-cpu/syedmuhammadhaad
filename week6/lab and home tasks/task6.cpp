#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of chords: ";
    cin >> n;
    cin.ignore();

    string chords[n];
    cout << "Enter chords one per line:\n";
    for(int i = 0; i < n; i++) {
        getline(cin, chords[i]);
    }

    for(int i = 0; i < n; i++) {
        if(chords[i].back() != '7') { 
            chords[i] += '7';
        }
    }

    cout << "Jazzified chords: [";
    for(int i = 0; i < n; i++) {
        cout << chords[i];
        if(i != n-1) cout << ", ";
    }
    cout << "]";

    return 0;
}