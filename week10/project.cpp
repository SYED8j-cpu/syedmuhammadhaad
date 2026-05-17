#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Limits and Global Storage
const int MAX = 100;
int ids[MAX];
string owners[MAX];
double prices[MAX];
string types[MAX];
string history[50];

int houseCount = 0;
int historyCount = 0;

// File names
const string DATA_FILE    = "properties.txt";
const string HISTORY_FILE = "history.txt";

// --- FUNCTION PROTOTYPES ---
void logAction(string action);
void pause();
void addHouse();
void displayAll();
void updateHouse();
void deleteHouse();
void searchByID();
void sortByPrice();
void sortByID();
void viewHistory();
void clearAll();
void saveToFile();
void loadFromFile();
void saveHistoryToFile();
void loadHistoryFromFile();

// ============================================================
//  FILE HANDLING — Save all properties to properties.txt
// ============================================================
void saveToFile()
{
    ofstream file(DATA_FILE);
    if (!file)
    {
        cout << "[ERROR] Cannot open file for writing." << endl;
        return;
    }

    file << houseCount << "\n";                          // first line = record count
    for (int i = 0; i < houseCount; i++)
    {
        file << ids[i]    << "\n"
             << owners[i] << "\n"
             << types[i]  << "\n"
             << prices[i] << "\n";
    }
    file.close();
    cout << "[FILE] Data saved to " << DATA_FILE << endl;
}

// ============================================================
//  FILE HANDLING — Load properties from properties.txt
// ============================================================
void loadFromFile()
{
    ifstream file(DATA_FILE);
    if (!file)
    {
        cout << "[FILE] No existing data file found. Starting fresh." << endl;
        return;
    }

    file >> houseCount;
    file.ignore();                                       // discard trailing newline

    for (int i = 0; i < houseCount; i++)
    {
        file >> ids[i];
        file.ignore();
        getline(file, owners[i]);
        getline(file, types[i]);
        file >> prices[i];
        file.ignore();
    }
    file.close();
    cout << "[FILE] " << houseCount << " record(s) loaded from " << DATA_FILE << endl;
}

// ============================================================
//  FILE HANDLING — Append one history entry to history.txt
// ============================================================
void saveHistoryToFile()
{
    if (historyCount == 0) return;

    ofstream file(HISTORY_FILE, ios::app);               // append mode
    if (!file)
    {
        cout << "[ERROR] Cannot open history file." << endl;
        return;
    }
    // Write only the latest entry (last one added)
    file << history[historyCount - 1] << "\n";
    file.close();
}

// ============================================================
//  FILE HANDLING — Load all past history from history.txt
// ============================================================
void loadHistoryFromFile()
{
    ifstream file(HISTORY_FILE);
    if (!file)
    {
        cout << "[FILE] No history file found." << endl;
        return;
    }

    string line;
    while (getline(file, line) && historyCount < 50)
        history[historyCount++] = line;

    file.close();
    cout << "[FILE] " << historyCount << " history entry/entries loaded." << endl;
}

// ============================================================
//  EXISTING FUNCTIONS (unchanged logic, saveToFile added)
// ============================================================

void logAction(string action)
{
    if (historyCount < 50)
    {
        history[historyCount++] = action;
        saveHistoryToFile();                             // persist immediately
    }
}

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void addHouse()
{
    if (houseCount < MAX)
    {
        cout << "Enter House ID: ";
        cin >> ids[houseCount];
        cin.ignore();
        cout << "Enter Owner Name: ";
        getline(cin, owners[houseCount]);
        cout << "Enter Property Type: ";
        getline(cin, types[houseCount]);
        cout << "Enter Price: $";
        cin >> prices[houseCount];
        houseCount++;
        logAction("Added Property ID: " + to_string(ids[houseCount - 1]));
        saveToFile();                                    // persist after add
        cout << "[SUCCESS] Property added!";
    }
    else
        cout << "[ERROR] System full!";
}

void displayAll()
{
    cout << "\n--- ALL PROPERTIES ---" << endl;
    if (houseCount == 0)
        cout << "No records found." << endl;
    for (int i = 0; i < houseCount; i++)
    {
        cout << "ID: " << ids[i]
             << " | Owner: " << owners[i]
             << " | Type: "  << types[i]
             << " | Price: $" << prices[i] << endl;
    }
    logAction("Viewed all properties.");
}

void updateHouse()
{
    int id, found = -1;
    cout << "Enter ID to update: ";
    cin >> id;
    for (int i = 0; i < houseCount; i++)
        if (ids[i] == id) { found = i; break; }

    if (found != -1)
    {
        cin.ignore();
        cout << "New Owner: ";
        getline(cin, owners[found]);
        cout << "New Price: ";
        cin >> prices[found];
        logAction("Updated Property ID: " + to_string(id));
        saveToFile();                                    // persist after update
        cout << "[SUCCESS] Record updated!";
    }
    else
        cout << "Not found.";
}

void deleteHouse()
{
    int id, found = -1;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (int i = 0; i < houseCount; i++)
        if (ids[i] == id) { found = i; break; }

    if (found != -1)
    {
        for (int i = found; i < houseCount - 1; i++)
        {
            ids[i]    = ids[i + 1];
            owners[i] = owners[i + 1];
            prices[i] = prices[i + 1];
            types[i]  = types[i + 1];
        }
        houseCount--;
        logAction("Deleted Property ID: " + to_string(id));
        saveToFile();                                    // persist after delete
        cout << "[SUCCESS] Deleted!";
    }
    else
        cout << "Not found.";
}

void searchByID()
{
    int id;
    cout << "Enter ID: ";
    cin >> id;
    for (int i = 0; i < houseCount; i++)
    {
        if (ids[i] == id)
        {
            cout << "Found -> Owner: " << owners[i]
                 << ", Price: $" << prices[i] << endl;
            logAction("Searched for ID: " + to_string(id));
            return;
        }
    }
    cout << "Not found.";
}

void sortByPrice()
{
    for (int i = 0; i < houseCount - 1; i++)
        for (int j = 0; j < houseCount - i - 1; j++)
            if (prices[j] < prices[j + 1])
            {
                swap(prices[j], prices[j + 1]);
                swap(ids[j],    ids[j + 1]);
                swap(owners[j], owners[j + 1]);
                swap(types[j],  types[j + 1]);
            }

    logAction("Sorted by Price.");
    saveToFile();                                        // persist new order
    cout << "[SUCCESS] Sorted by Price (High to Low).";
}

void sortByID()
{
    for (int i = 0; i < houseCount - 1; i++)
        for (int j = 0; j < houseCount - i - 1; j++)
            if (ids[j] > ids[j + 1])
            {
                swap(ids[j],    ids[j + 1]);
                swap(prices[j], prices[j + 1]);
                swap(owners[j], owners[j + 1]);
                swap(types[j],  types[j + 1]);
            }

    logAction("Sorted by ID.");
    saveToFile();                                        // persist new order
    cout << "[SUCCESS] Sorted by ID (Low to High).";
}

void viewHistory()
{
    cout << "\n--- SESSION HISTORY ---" << endl;
    for (int i = 0; i < historyCount; i++)
        cout << i + 1 << ". " << history[i] << endl;
}

void clearAll()
{
    houseCount = 0;
    logAction("Cleared all records.");
    saveToFile();                                        // overwrite file with 0 records
    cout << "[SUCCESS] All data wiped!";
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    // Load persisted data at startup
    loadFromFile();
    loadHistoryFromFile();

    int roleChoice, choice = 0;
    bool isAdmin = false;

    cout << "====================================" << endl;
    cout << "    HOUSE MANAGEMENT SYSTEM" << endl;
    cout << "====================================" << endl;
    cout << "1. Admin (Staff)\n2. User (Client)\nEnter Role: ";
    cin >> roleChoice;

    if (roleChoice == 1)
    {
        string pass;
        cout << "Enter Admin Password: ";
        cin >> pass;
        if (pass == "admin123")
            isAdmin = true;
        else
        {
            cout << "Wrong password! Continuing as User." << endl;
            isAdmin = false;
        }
    }

    while (choice != 10)
    {
        cout << "\nLogged in as: " << (isAdmin ? "ADMIN" : "USER") << endl;
        cout << "====================================" << endl;
        cout << "1. Add Property (Admin)"             << endl;
        cout << "2. Display All Properties"           << endl;
        cout << "3. Update Property (Admin)"          << endl;
        cout << "4. Delete Property (Admin)"          << endl;
        cout << "5. Search by House ID"               << endl;
        cout << "6. Sort by Price (High to Low)"      << endl;
        cout << "7. Sort by ID (Low to High)"         << endl;
        cout << "8. View Action History"              << endl;
        cout << "9. Clear All Records (Admin)"        << endl;
        cout << "10. Exit"                            << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:  isAdmin ? addHouse()    : (void)(cout << "[DENIED] Admin only."); break;
        case 2:  displayAll();  break;
        case 3:  isAdmin ? updateHouse() : (void)(cout << "[DENIED] Admin only."); break;
        case 4:  isAdmin ? deleteHouse() : (void)(cout << "[DENIED] Admin only."); break;
        case 5:  searchByID();  break;
        case 6:  sortByPrice(); break;
        case 7:  sortByID();    break;
        case 8:  viewHistory(); break;
        case 9:  isAdmin ? clearAll()    : (void)(cout << "[DENIED] Admin only."); break;
        }

        if (choice >= 1 && choice <= 9)
            pause();
    }

    cout << "Goodbye!" << endl;
    return 0;
}