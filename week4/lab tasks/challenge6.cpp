#include <iostream>
using namespace std;

int main() {
    // Input Data
    double monthlySalary = 10000;
    double laptopPrice = 50000;
    int monthsAsked = 6;
    double advanceRate = 0.50;

    // Calculations
    double monthlyAdvance = monthlySalary * advanceRate;
    double totalAdvance = monthlyAdvance * monthsAsked;

    // Decision Logic
    if (totalAdvance >= laptopPrice) {
        cout << "Ali can buy the laptop!" << endl;
        cout << "Total Advance Received: Rs " << totalAdvance << endl;
    } 
    else {
        cout << "Ali cannot buy the laptop with a 6-month advance." << endl;
        cout << "Total Advance: Rs " << totalAdvance << " (Short by Rs " << (laptopPrice - totalAdvance) << ")" << endl;
        
        // Suggest required months
        int requiredMonths = laptopPrice / monthlyAdvance;
        cout << "Suggestion: Ali needs a 50% advance for " << requiredMonths << " months to buy the laptop." << endl;}
}