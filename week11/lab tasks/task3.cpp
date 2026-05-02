#include <iostream>
using namespace std;

const int colSize = 3;

void printSum(int matrix[][colSize], int rowSize) {
    int sum = 0;
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            sum += matrix[row][col];
        }
    }
    cout << "The sum of elements in the matrix is: " << sum << endl;
}

int main() {
    int rowSize;
    cout << "Enter row size: ";
    cin >> rowSize;

    int matrix[100][colSize]; // max 100 rows

    cout << "Enter the elements of the matrix:" << endl;
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            cout << "Enter element at position [" << row << "][" << col << "]: ";
            cin >> matrix[row][col];
        }
    }

    printSum(matrix, rowSize);

    return 0;
}