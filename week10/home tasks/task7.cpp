// Task 07 (CP): Bank Balance Interest Calculator

#include <iostream>
using namespace std;

float calculateBalance(float balance, int years)
{
    float interestRate = 0;

    // Base interest rate by balance
    if (balance < 10000)
    {
        interestRate = 5;
    }
    else if (balance <= 50000)
    {
        interestRate = 7;
    }
    else
    {
        interestRate = 10;
    }

    // Extra interest for long-term accounts
    if (years >= 3)
    {
        interestRate += 2;
    }

    float interest = balance * (interestRate / 100.0f);
    return balance + interest;
}

int main()
{
    float balance;
    int years;

    cout << "Enter Balance and years: " << endl;
    cin >> balance >> years;

    float updatedBalance = calculateBalance(balance, years);
    cout << "Updated Balance: " << updatedBalance << endl;

    return 0;
}