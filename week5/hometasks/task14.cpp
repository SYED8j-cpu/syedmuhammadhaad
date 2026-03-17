#include <iostream>

using namespace std;

int main()
{
    int choice;
    double num1, num2;

    do
    {

        cout << "\n--- Simple Calculator Menu ---" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. Clear Screen" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (choice == 6)
        {
            cout << "Exiting Calculator. Goodbye!" << endl;
            break;
        }

        if (choice >= 1 && choice <= 4)
        {
            cout << "Enter two numbers: ";
            cin >> num1 >> num2;

            switch (choice)
            {
            case 1:
                cout << "Result: " << num1 + num2 << endl;
                break;
            case 2:
                cout << "Result: " << num1 - num2 << endl;
                break;
            case 3:
                cout << "Result: " << num1 * num2 << endl;
                break;
            case 4:
                if (num2 != 0)
                    cout << "Result: " << num1 / num2 << endl;
                else
                    cout << "Error: Division by zero is not allowed." << endl;
                break;
            }
        }

        else if (choice == 5)
        {
            cout << "Screen cleared." << endl;

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}
