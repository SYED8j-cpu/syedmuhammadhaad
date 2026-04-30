// Task 06 (CP): Strong Number Checker
// A number is Strong if sum of factorials of its digits == the number
// Example: 145 → 1! + 4! + 5! = 1 + 24 + 120 = 145 ✓

#include <iostream>
using namespace std;

// Helper function: calculates factorial of a single digit
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Main function: checks if num is a Strong Number
bool isStrong(int num) {
    int temp = num;
    int sumOfFactorials = 0;

    while (temp > 0) {
        int digit = temp % 10;
        sumOfFactorials += factorial(digit);
        temp /= 10;
    }

    return sumOfFactorials == num;
}

int main() {
    int num;
    cin >> num;

    if (isStrong(num)) {
        cout << "Strong Number" << endl;
    } else {
        cout << "Not Strong Number" << endl;
    }

    return 0;
}