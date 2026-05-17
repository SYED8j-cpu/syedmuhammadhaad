#include <iostream>
using namespace std;

const int colSize = 5;

void printCars(int cars[][colSize], int rowSize)
{
    for (int row = 0; row < rowSize; row++)
    {
        for (int col = 0; col < colSize; col++)
        {
            cout << cars[row][col] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    const int rowSize = 5;
    int cars[rowSize][colSize] = {
        {10, 7, 12, 10, 4},
        {18, 11, 15, 17, 2},
        {23, 19, 12, 16, 14},
        {7, 12, 16, 0, 2},
        {3, 5, 6, 2, 1}};

    cout << "Car Data Matrix:" << endl;
    printCars(cars, rowSize);

    return 0;
}