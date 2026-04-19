#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Limits and Arrays
    const int MAX = 100;
    int ids[MAX];
    string names[MAX];
    float gpas[MAX];
    string history[50]; // History log

    int studentCount = 0;
    int historyCount = 0;
    int choice = 0;

    while (choice != 10)
    {
        // Simple Menu
        cout << "\n====================================" << endl;
        cout << "    STUDENT MANAGEMENT SYSTEM" << endl;
        cout << "====================================" << endl;
        cout << "1. Add Student (Create)" << endl;
        cout << "2. Display All (Read)" << endl;
        cout << "3. Update Student (Update)" << endl;
        cout << "4. Delete Student (Delete)" << endl;
        cout << "5. Search by ID" << endl;
        cout << "6. Sort by GPA (High to Low)" << endl;
        cout << "7. Sort by ID (Low to High)" << endl;
        cout << "8. View Action History" << endl;
        cout << "9. Clear All Records" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore(); // Clean buffer after choice

        // 1. ADD STUDENT
        if (choice == 1)
        {
            if (studentCount < MAX)
            {
                cout << "Enter ID: ";
                cin >> ids[studentCount];
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, names[studentCount]);
                cout << "Enter GPA: ";
                cin >> gpas[studentCount];
                cin.ignore();

                studentCount++;
                if (historyCount < 50)
                    history[historyCount++] = "Added a student.";
                cout << "\n[SUCCESS] Student added!";
            }
            else
            {
                cout << "\n[ERROR] System full!";
            }
        }

        // 2. DISPLAY ALL
        else if (choice == 2)
        {
            cout << "\n--- ALL RECORDS ---" << endl;
            if (studentCount == 0)
                cout << "No records found." << endl;
            for (int i = 0; i < studentCount; i++)
            {
                cout << "ID: " << ids[i] << " | Name: " << names[i] << " | GPA: " << gpas[i] << endl;
            }
            if (historyCount < 50)
                history[historyCount++] = "Viewed all records.";
        }

        // 3. UPDATE STUDENT
        else if (choice == 3)
        {
            int sid, found = -1;
            cout << "Enter ID to update: ";
            cin >> sid;
            for (int i = 0; i < studentCount; i++)
            {
                if (ids[i] == sid)
                {
                    found = i;
                    break;
                }
            }
            if (found != -1)
            {
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, names[found]);
                cout << "Enter New GPA: ";
                cin >> gpas[found];
                cin.ignore();
                if (historyCount < 50)
                    history[historyCount++] = "Updated a student.";
                cout << "\n[SUCCESS] Record updated!";
            }
            else
                cout << "\n[ERROR] Student not found.";
        }

        // 4. DELETE STUDENT
        else if (choice == 4)
        {
            int did, found = -1;
            cout << "Enter ID to delete: ";
            cin >> did;
            for (int i = 0; i < studentCount; i++)
            {
                if (ids[i] == did)
                {
                    found = i;
                    break;
                }
            }
            if (found != -1)
            {
                for (int i = found; i < studentCount - 1; i++)
                {
                    ids[i] = ids[i + 1];
                    names[i] = names[i + 1];
                    gpas[i] = gpas[i + 1];
                }
                studentCount--;
                if (historyCount < 50)
                    history[historyCount++] = "Deleted a student.";
                cout << "\n[SUCCESS] Student deleted!";
            }
            else
                cout << "\n[ERROR] Student not found.";
        }

        // 5. SEARCH BY ID
        else if (choice == 5)
        {
            int sid;
            cout << "Enter ID: ";
            cin >> sid;
            bool found = false;
            for (int i = 0; i < studentCount; i++)
            {
                if (ids[i] == sid)
                {
                    cout << "Found -> Name: " << names[i] << ", GPA: " << gpas[i] << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Not found.";
            if (historyCount < 50)
                history[historyCount++] = "Searched for student.";
        }

        // 6. SORT BY GPA (Bubble Sort)
        else if (choice == 6)
        {
            for (int i = 0; i < studentCount - 1; i++)
            {
                for (int j = 0; j < studentCount - i - 1; j++)
                {
                    if (gpas[j] < gpas[j + 1])
                    {
                        swap(gpas[j], gpas[j + 1]);
                        swap(ids[j], ids[j + 1]);
                        swap(names[j], names[j + 1]);
                    }
                }
            }
            cout << "\n[SUCCESS] Sorted by GPA (Descending)!";
            if (historyCount < 50)
                history[historyCount++] = "Sorted by GPA.";
        }

        // 7. SORT BY ID (Bubble Sort)
        else if (choice == 7)
        {
            for (int i = 0; i < studentCount - 1; i++)
            {
                for (int j = 0; j < studentCount - i - 1; j++)
                {
                    if (ids[j] > ids[j + 1])
                    {
                        swap(ids[j], ids[j + 1]);
                        swap(gpas[j], gpas[j + 1]);
                        swap(names[j], names[j + 1]);
                    }
                }
            }
            cout << "\n[SUCCESS] Sorted by ID (Ascending)!";
            if (historyCount < 50)
                history[historyCount++] = "Sorted by ID.";
        }

        // 8. VIEW HISTORY
        else if (choice == 8)
        {
            cout << "\n--- SESSION HISTORY ---" << endl;
            for (int i = 0; i < historyCount; i++)
                cout << i + 1 << ". " << history[i] << endl;
        }

        // 9. CLEAR ALL
        else if (choice == 9)
        {
            studentCount = 0;
            cout << "\n[SUCCESS] All records wiped!";
            if (historyCount < 50)
                history[historyCount++] = "Cleared all records.";
        }

        // THE PAUSE LOGIC (Runs after every choice except Exit)
        if (choice >= 1 && choice <= 9)
        {
            cout << "\n\nPress Enter to return to main menu...";
            cin.get(); // Waits for user input
        }
    }

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
