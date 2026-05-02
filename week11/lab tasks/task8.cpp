#include <iostream>
using namespace std;

const int colSize = 3;

int countIdenticalArrays(int arr[][colSize], int rowSize) {
    int count = 0;

    for (int i = 0; i < rowSize; i++) {
        for (int j = i + 1; j < rowSize; j++) {
            bool identical = true;
            for (int col = 0; col < colSize; col++) {
                if (arr[i][col] != arr[j][col]) {
                    identical = false;
                    break;
                }
            }
            if (identical) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int rowSize;
    cout << "Enter the number of rows for the array: ";
    cin >> rowSize;

    int arr[100][colSize];

    cout << "Enter the elements of the array:" << endl;
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            cout << "Enter element at position [" << row << "][" << col << "]: ";
            cin >> arr[row][col];
        }
    }

    int result = countIdenticalArrays(arr, rowSize);
    cout << "The count of identical rows in the array is: " << result << endl;

    return 0;
}