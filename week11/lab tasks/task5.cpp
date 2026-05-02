#include <iostream>
#include <string>
using namespace std;

const int SIZE = 5;

string fire(string grid[][SIZE], string coordinate) {
    // Coordinate format: letter (A-E) + number (1-5)
    // A=row0, B=row1, C=row2, D=row3, E=row4
    // 1=col0, 2=col1, 3=col2, 4=col3, 5=col4

    int row = coordinate[0] - 'A';
    int col = coordinate[1] - '1';

    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return "Invalid coordinate!";
    }

    if (grid[row][col] == "*") {
        return "BOOM";
    } else {
        return "splash";
    }
}

int main() {
    string grid[SIZE][SIZE] = {
        {".", ".", ".", "*", "*"},
        {".", "*", ".", ".", "."},
        {".", "*", ".", ".", "."},
        {".", "*", ".", ".", "."},
        {".", ".", "*", "*", "."}
    };

    cout << "Battleship Grid:" << endl;
    cout << "  1 2 3 4 5" << endl;
    for (int row = 0; row < SIZE; row++) {
        cout << (char)('A' + row) << " ";
        for (int col = 0; col < SIZE; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }

    string coordinate;
    cout << "\nEnter coordinate to fire torpedo (e.g., A1, B3, E5): ";
    cin >> coordinate;

    cout << "Result: " << fire(grid, coordinate) << endl;

    return 0;
}