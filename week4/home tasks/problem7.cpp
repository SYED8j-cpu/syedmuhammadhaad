#include <iostream>
# include <string>
# include <cmath>
using namespace std;

int main()
{
    string type;
    double area;
    cin >> type;

    if (type == "Square")
    {
        double side;
        cin >> side;
        area = side * side;
        cout << area << endl;
    }
    else if (type == "Rectangle")
    {
        double length, width;
        cin >> length >> width;
        area = length * width;
        cout << area << endl;
    }
    else if (type == "Circle")
    {
        double radius;
        cin >> radius;
        area = 3.14 * radius * radius;
        cout << area << endl;
    }
    else if (type == "Triangle")
    {
        double base, height;
        cin >> base >> height;
        area = 0.5 * base * height;
        cout << area << endl;
    }
}
