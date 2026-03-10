#include <iostream>
using namespace std;

int main()
{
    cout << "enter matric marks:" << endl;
    float matric;
    cin >> matric;

    cout << "enter inter marks:" << endl;
    float inter;
    cin >> inter;

    cout << "enter ecat marks:" << endl;
    float ecat;
    cin >> ecat;

    float aggregate;
    // use floating-point calculation to avoid integer division
    aggregate = (matric * 10.0f) / 1100.0f
              + (inter * 40.0f) / 1200.0f
              + (ecat * 50.0f) / 400.0f;

    cout << "your aggregate:" << aggregate << "%";
    return 0;
}