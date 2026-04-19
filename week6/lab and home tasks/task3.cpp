#include <iostream>
using namespace std;
main()
{
    int pin[3], choice, deposit_amount, withdraw_amount;
    int account_balance = 0;
    int correct_pin = 1234;
    choice = 0;
    for (int i = 1; i <= 3; i++)
    {
        cout << "enter your pin: ";
        cin >> pin[i];
        if (pin[i] == correct_pin)
        {
            cout << "Login Successful.\n";

            while (choice != 4)
            {
                cout << "\n-------ATM--------\n";
                cout << "1. Check Balance\n";
                cout << "2. Deposit Money\n";
                cout << "3. Withdraw Money\n";
                cout << "4. Exit\n";
                cout << "------------------\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                {
                    cout << "Your current account balance is " << account_balance << endl;
                }
                else if (choice == 2)
                {
                    cout << "enter an amount to deposit: ";
                    cin >> deposit_amount;
                    account_balance += deposit_amount;
                    cout << "Money deposited successfully.\n";
                }
                else if (choice == 3)
                {
                    cout << "Enter an amount to withdraw: ";
                    cin >> withdraw_amount;
                    if (withdraw_amount <= account_balance)
                    {
                        cout << "Withdraw Successful.\n";
                        account_balance -= withdraw_amount;
                    }
                    else
                    {
                        cout << "Insufficient Account Balance\n";
                    }
                }
                else if (choice == 4)
                {
                    cout << "Exiting...\n";
                    cout << "Thank you for using ATM..\n";
                    i = 6;
                    break;
                }
                else
                {
                    cout << "Wrong choice. Please Enter a valid Choice.\n";
                }
            }
        }
        else
        {
            cout << "Wrong pin.\ntry again\n";
            if (i == 3)
            {
                cout << "Too many attempts. Card blocked...";
            }
        }
    }
}