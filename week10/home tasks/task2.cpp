// Task 02 (CP): Pyramid Volume Calculator
// Volume of pyramid = (1/3) * length * width * height
// Input is in meters, output in desired unit

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

string pyramidVolume(double length, double width, double height, string unit) {
    // Calculate volume in cubic meters first
    double volumeMeters = (1.0 / 3.0) * length * width * height;

    double convertedVolume;

    if (unit == "millimeters") {
        // 1 meter = 1000 mm → 1 cubic meter = 1000^3 cubic mm
        convertedVolume = volumeMeters * 1e9;
    } else if (unit == "centimeters") {
        // 1 meter = 100 cm → 1 cubic meter = 100^3 cubic cm
        convertedVolume = volumeMeters * 1e6;
    } else if (unit == "meters") {
        convertedVolume = volumeMeters;
    } else if (unit == "kilometers") {
        // 1 meter = 0.001 km → 1 cubic meter = 0.001^3 cubic km
        convertedVolume = volumeMeters * 1e-9;
    } else {
        return "Invalid unit!";
    }

    ostringstream oss;
    oss << fixed << setprecision(3) << convertedVolume << " cubic " << unit;
    return oss.str();
}

int main() {
    double length, width, height;
    string unit;

    cout << "Enter length, width, height (in meters): ";
    cin >> length >> width >> height;

    cout << "Enter output unit (millimeters, centimeters, meters, kilometers): ";
    cin >> unit;

    cout << pyramidVolume(length, width, height, unit) << endl;

    return 0;
}