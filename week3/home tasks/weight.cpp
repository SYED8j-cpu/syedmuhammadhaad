#include <iostream>
#include <string> // Added for robust string handling

using namespace std;

int main() {
    cout << "enter your name:" << endl;
    string n;
    cin >> n;
    cout << "enter weight in kilograms:" << endl;
    int w;
    cin >> w;
    
    int days;
    days = w * 15;
    
    // Fixed output formatting with added spaces for readability
    cout << "enter name: " << n << endl;
    cout << "enter weight in kilograms: " << w << endl;
    cout << n << " will need " << days << " days to lose weight by doctor's suggestion" << endl;
    
    return 0; // Good practice to include return 0
}
