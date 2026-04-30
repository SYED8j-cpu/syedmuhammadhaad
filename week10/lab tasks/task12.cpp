// Task 12: Banking Management System using Functions
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// ─── Function Prototypes ───────────────────────────────────────────────────
bool login();
void menu();
void createAccount(string names[], double balances[], int &count);
void viewAccounts(string names[], double balances[], int count);
void deposit(string names[], double balances[], int count);
void withdraw(string names[], double balances[], int count);
void checkBalance(string names[], double balances[], int count);
int findAccount(string names[], int count, string name);

// ─── Main ──────────────────────────────────────────────────────────────────
int main()
{
    if (!login())
        return 0;

    string accountNames[MAX];
    double accountBalances[MAX];
    int accountCount = 0;
    int choice;

    while (true)
    {
        menu();
        cin >> choice;

        if (choice == 1)
            createAccount(accountNames, accountBalances, accountCount);
        else if (choice == 2)
            viewAccounts(accountNames, accountBalances, accountCount);
        else if (choice == 3)
            deposit(accountNames, accountBalances, accountCount);
        else if (choice == 4)
            withdraw(accountNames, accountBalances, accountCount);
        else if (choice == 5)
            checkBalance(accountNames, accountBalances, accountCount);
        else if (choice == 6)
        {
            cout << "Thank you for using our Banking System. Goodbye!" << endl;
            return 0;
        }
        else
            cout << "Invalid Choice. Please try again." << endl;
    }
}

// ─── Login ─────────────────────────────────────────────────────────────────
bool login()
{
    string username, password;

    for (int i = 1; i <= 3; i++)
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == "admin" && password == "1234")
        {
            cout << "Login Successful! Welcome to the Banking System." << endl;
            return true;
        }
        else
            cout << "Wrong credentials. Attempts remaining: " << (3 - i) << endl;
    }

    cout << "Too many failed attempts. Program End." << endl;
    return false;
}

// ─── Menu ──────────────────────────────────────────────────────────────────
void menu()
{
    cout << "\n========== Banking Management System ==========" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. View All Accounts" << endl;
    cout << "3. Deposit Money" << endl;
    cout << "4. Withdraw Money" << endl;
    cout << "5. Check Balance" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter Choice: ";
}

// ─── Find Account (helper) ─────────────────────────────────────────────────
// Returns the index of the account with the given name, or -1 if not found
int findAccount(string names[], int count, string name)
{
    for (int i = 0; i < count; i++)
    {
        if (names[i] == name)
            return i;
    }
    return -1;
}

// ─── Create Account ────────────────────────────────────────────────────────
void createAccount(string names[], double balances[], int &count)
{
    if (count >= MAX)
    {
        cout << "Account storage full!" << endl;
        return;
    }

    cout << "Enter Account Holder Name: ";
    cin >> names[count];

    cout << "Enter Initial Deposit Amount: $";
    cin >> balances[count];

    if (balances[count] < 0)
    {
        cout << "Initial deposit cannot be negative. Account not created." << endl;
        return;
    }

    count++;
    cout << "Account Created Successfully!" << endl;
}

// ─── View All Accounts ─────────────────────────────────────────────────────
void viewAccounts(string names[], double balances[], int count)
{
    if (count == 0)
    {
        cout << "No accounts found." << endl;
        return;
    }

    cout << "\n--- All Accounts ---" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "Account #" << i + 1 << endl;
        cout << "Name   : " << names[i] << endl;
        cout << "Balance: $" << balances[i] << endl;
        cout << "--------------------" << endl;
    }
}

// ─── Deposit ───────────────────────────────────────────────────────────────
void deposit(string names[], double balances[], int count)
{
    string name;
    double amount;

    cout << "Enter Account Holder Name: ";
    cin >> name;

    int index = findAccount(names, count, name);

    if (index == -1)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter Deposit Amount: $";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Deposit amount must be positive." << endl;
        return;
    }

    balances[index] += amount;
    cout << "Deposit Successful! New Balance: $" << balances[index] << endl;
}

// ─── Withdraw ──────────────────────────────────────────────────────────────
void withdraw(string names[], double balances[], int count)
{
    string name;
    double amount;

    cout << "Enter Account Holder Name: ";
    cin >> name;

    int index = findAccount(names, count, name);

    if (index == -1)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter Withdrawal Amount: $";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Withdrawal amount must be positive." << endl;
        return;
    }

    if (amount > balances[index])
    {
        cout << "Insufficient funds. Current Balance: $" << balances[index] << endl;
        return;
    }

    balances[index] -= amount;
    cout << "Withdrawal Successful! Remaining Balance: $" << balances[index] << endl;
}

// ─── Check Balance ─────────────────────────────────────────────────────────
void checkBalance(string names[], double balances[], int count)
{
    string name;

    cout << "Enter Account Holder Name: ";
    cin >> name;

    int index = findAccount(names, count, name);

    if (index == -1)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Account Holder: " << names[index] << endl;
    cout << "Current Balance: $" << balances[index] << endl;
}