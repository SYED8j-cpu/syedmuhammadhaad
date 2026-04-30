// Task 03 (CP): Vehicle Tax Calculator

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

float taxCalculator(char type, float price) {
    float taxRate = 0;
    string vehicleType;

    switch (type) {
        case 'M': taxRate = 6;  vehicleType = "Motorcycle"; break;
        case 'E': taxRate = 8;  vehicleType = "Electric";   break;
        case 'S': taxRate = 10; vehicleType = "Sedan";      break;
        case 'V': taxRate = 12; vehicleType = "Van";        break;
        case 'T': taxRate = 15; vehicleType = "Truck";      break;
        default:
            cout << "Invalid vehicle type!" << endl;
            return -1;
    }

    float taxAmount = price * (taxRate / 100.0f);
    float finalPrice = price + taxAmount;

    cout << "The final price on a vehicle of type " << vehicleType
         << " after adding the tax is $" << finalPrice << endl;

    return finalPrice;
}

int main() {
    char type;
    float price;

    cout << "Enter Vehicle Type Code (M/E/S/V/T): ";
    cin >> type;

    cout << "Enter Vehicle Price: ";
    cin >> price;

    taxCalculator(type, price);

    return 0;
}