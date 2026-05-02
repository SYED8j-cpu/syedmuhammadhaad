#include <iostream>
#include <string>
using namespace std;

const int colSize = 5;
const int rowSize = 5;

// Row indices: 0=Suzuki, 1=Toyota, 2=Nissan, 3=BMW, 4=Audi
// Col indices: 0=Red, 1=Black, 2=Brown, 3=Blue, 4=Gray

// A: Print Toyota Blue cars
void printToyotaBlue(int cars[][colSize]) {
    cout << "A) Toyota Blue cars available: " << cars[1][3] << endl;
}

// B: Return total number of Red cars
int totalRedCars(int cars[][colSize]) {
    int total = 0;
    for (int row = 0; row < rowSize; row++) {
        total += cars[row][0]; // column 0 = Red
    }
    return total;
}

// C: Return total number of Nissan cars
int totalNissanCars(int cars[][colSize]) {
    int total = 0;
    for (int col = 0; col < colSize; col++) {
        total += cars[2][col]; // row 2 = Nissan
    }
    return total;
}

// D: Return total cars of a given color (0=Red,1=Black,2=Brown,3=Blue,4=Gray)
int converter(int cars[][colSize], int colorIndex) {
    int total = 0;
    for (int row = 0; row < rowSize; row++) {
        total += cars[row][colorIndex];
    }
    return total;
}

// E: Print transposed matrix (rows become columns)
void printTranspose(int cars[][colSize]) {
    cout << "E) Transposed Matrix:" << endl;
    for (int col = 0; col < colSize; col++) {
        for (int row = 0; row < rowSize; row++) {
            cout << cars[row][col] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int cars[rowSize][colSize] = {
        {10, 7, 12, 10, 4},   // Suzuki
        {18, 11, 15, 17, 2},  // Toyota
        {23, 19, 12, 16, 14}, // Nissan
        {7, 12, 16, 0, 2},    // BMW
        {3, 5, 6, 2, 1}       // Audi
    };

    // A
    printToyotaBlue(cars);

    // B
    cout << "B) Total Red cars: " << totalRedCars(cars) << endl;

    // C
    cout << "C) Total Nissan cars: " << totalNissanCars(cars) << endl;

    // D
    string colorNames[] = {"Red", "Black", "Brown", "Blue", "Gray"};
    int colorChoice;
    cout << "\nD) Enter color index (0=Red, 1=Black, 2=Brown, 3=Blue, 4=Gray): ";
    cin >> colorChoice;
    if (colorChoice >= 0 && colorChoice < colSize) {
        cout << "Total " << colorNames[colorChoice] << " cars: "
             << converter(cars, colorChoice) << endl;
    } else {
        cout << "Invalid color index!" << endl;
    }

    // E
    cout << endl;
    printTranspose(cars);

    return 0;
}