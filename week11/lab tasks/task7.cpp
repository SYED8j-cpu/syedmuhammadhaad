#include <iostream>
using namespace std;

const int colSize = 5;

void largestColumnFirst(int matrix[][colSize], int rowSize) {
    // Find column sums
    int colSums[colSize] = {0};
    for (int col = 0; col < colSize; col++) {
        for (int row = 0; row < rowSize; row++) {
            colSums[col] += matrix[row][col];
        }
    }

    // Find index of largest sum column
    int maxCol = 0;
    for (int col = 1; col < colSize; col++) {
        if (colSums[col] > colSums[maxCol]) {
            maxCol = col;
        }
    }

    // Swap largest column with first column element by element
    if (maxCol != 0) {
        for (int row = 0; row < rowSize; row++) {
            int temp = matrix[row][0];
            matrix[row][0] = matrix[row][maxCol];
            matrix[row][maxCol] = temp;
        }
    }
}

void printMatrix(int matrix[][colSize], int rowSize) {
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            cout << matrix[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rowSize;
    cout << "Enter row size: ";
    cin >> rowSize;

    int matrix[100][colSize];

    cout << "Enter the elements of the matrix:" << endl;
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            cout << "Enter element at position [" << row << "][" << col << "]: ";
            cin >> matrix[row][col];
        }
    }

    cout << "\nOriginal Matrix:" << endl;
    printMatrix(matrix, rowSize);

    largestColumnFirst(matrix, rowSize);

    cout << "\nMatrix after largest column moved to first:" << endl;
    printMatrix(matrix, rowSize);

    return 0;
}