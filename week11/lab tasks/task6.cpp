#include <iostream>
#include <string>
using namespace std;

const int ROWS = 7;
const int COLS = 16;

// Goal scored if ball '0' is above the crossbar (row < 3) and between uprights.
// The uprights are '#' characters. The crossbar is row index 3 (the "######" row).
// Ball scores if it's in rows 0-2 AND horizontally between the two '#' uprights.
bool isGoalScored(string field[][COLS]) {
    // Find upright column positions from the crossbar row (row 3)
    // Then check if '0' is in rows 0-2 between those columns

    // Find left and right upright positions (look for '#' in rows 0-2)
    int leftUpright = -1, rightUpright = -1;
    for (int col = 0; col < COLS; col++) {
        if (field[0][col] == "#") {
            if (leftUpright == -1) leftUpright = col;
            else rightUpright = col;
        }
    }

    // Check if ball '0' is above crossbar (rows 0-2) and between uprights
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < COLS; col++) {
            if (field[row][col] == "0") {
                if (col > leftUpright && col < rightUpright) {
                    return true;
                }
            }
        }
    }
    return false;
}

void displayField(string field[][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            cout << field[row][col];
        }
        cout << endl;
    }
}

int main() {
    // Test Case 1: Ball below crossbar - false
    string field1[ROWS][COLS] = {
        {" "," ","#"," "," "," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#","#","#","#","#","#","#"," "," "," "," "," "," "," "},
        {" "," ","#"," ","0"," "," "," "," "," "," "," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," "," "," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," "," "," "," "," "," "," "}
    };

    // Test Case 2: Ball above crossbar between uprights - true
    string field2[ROWS][COLS] = {
        {" "," ","#"," "," "," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#"," ","0"," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," ","#"," "," "," "," "," "},
        {" "," ","#","#","#","#","#","#","#"," "," "," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," "," "," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," "," "," "," "," "," "," "},
        {" "," ","#"," "," "," "," "," "," "," "," "," "," "," "," "," "}
    };

    cout << "Test Case 1 Field:" << endl;
    displayField(field1);
    cout << "isGoalScored -> " << (isGoalScored(field1) ? "true" : "false") << endl;

    cout << "\nTest Case 2 Field:" << endl;
    displayField(field2);
    cout << "isGoalScored -> " << (isGoalScored(field2) ? "true" : "false") << endl;

    return 0;
}