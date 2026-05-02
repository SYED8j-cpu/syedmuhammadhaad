#include <iostream>
using namespace std;

const int SIZE = 3;

bool isIdentityMatrix(int matrix[][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (row == col && matrix[row][col] != 1) return false;
            if (row != col && matrix[row][col] != 0) return false;
        }
    }
    return true;
}

int main() {
    int matrix[SIZE][SIZE];

    cout << "Enter the elements of the matrix:" << endl;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << "Enter element at position [" << row << "][" << col << "]: ";
            cin >> matrix[row][col];
        }
    }

    cout << "\nThe matrix you entered is:" << endl;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << matrix[row][col] << "\t";
        }
        cout << endl;
    }

    if (isIdentityMatrix(matrix))
        cout << "The entered matrix is an identity matrix." << endl;
    else
        cout << "The entered matrix is NOT an identity matrix." << endl;

    return 0;
}