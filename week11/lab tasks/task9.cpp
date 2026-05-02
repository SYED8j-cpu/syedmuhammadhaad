#include <iostream>
using namespace std;

const int SIZE = 5;

char objects[SIZE][SIZE] = {
    {'-', '#', '#', '-', '#'},
    {'#', '-', '-', '#', '-'},
    {'-', '#', '-', '-', '-'},
    {'#', '-', '#', '-', '#'},
    {'#', '-', '-', '-', '-'}
};

bool gravity = false;
bool isBlackHole = false;

void displayWorld() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << objects[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void setGravityStatus(bool status) {
    gravity = status;
}

void timeTick(int times) {
    if (!gravity) return;

    for (int t = 0; t < times; t++) {
        if (isBlackHole) {
            // Black hole mode: blocks that reach row SIZE-1 wrap to row 0
            // Process from bottom to top
            for (int col = 0; col < SIZE; col++) {
                for (int row = SIZE - 1; row >= 0; row--) {
                    if (objects[row][col] == '#') {
                        int nextRow = (row + 1) % SIZE;
                        if (objects[nextRow][col] == '-') {
                            objects[nextRow][col] = '#';
                            objects[row][col] = '-';
                        }
                    }
                }
            }
        } else {
            // Normal gravity: blocks fall down, stop at bottom or on other blocks
            for (int col = 0; col < SIZE; col++) {
                for (int row = SIZE - 2; row >= 0; row--) {
                    if (objects[row][col] == '#') {
                        if (objects[row + 1][col] == '-') {
                            objects[row + 1][col] = '#';
                            objects[row][col] = '-';
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cout << "=== Normal Gravity (TimeTick 3) ===" << endl;
    cout << "Initial World:" << endl;
    displayWorld();

    setGravityStatus(true);
    timeTick(3);

    cout << "After TimeTick(3):" << endl;
    displayWorld();

    // Reset
    char reset[SIZE][SIZE] = {
        {'-', '#', '#', '-', '#'},
        {'#', '-', '-', '#', '-'},
        {'-', '#', '-', '-', '-'},
        {'#', '-', '#', '-', '#'},
        {'#', '-', '-', '-', '-'}
    };
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            objects[r][c] = reset[r][c];

    cout << "=== BlackHole Mode (TimeTick 1) ===" << endl;
    cout << "Initial World:" << endl;
    displayWorld();

    gravity = false;
    isBlackHole = true;
    setGravityStatus(true);
    timeTick(1);

    cout << "After TimeTick(1) with BlackHole:" << endl;
    displayWorld();

    // Reset again
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            objects[r][c] = reset[r][c];

    cout << "=== BlackHole Mode (TimeTick 2) ===" << endl;
    cout << "Initial World:" << endl;
    displayWorld();

    gravity = false;
    setGravityStatus(true);
    timeTick(2);

    cout << "After TimeTick(2) with BlackHole:" << endl;
    displayWorld();

    return 0;
}