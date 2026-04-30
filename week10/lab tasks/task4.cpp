// Task 04(CP): Calculate height of a tree using tan()
#include <iostream>
#include <cmath>
using namespace std;
 
int main()
{
    double distance, angleDegrees, angleRadians, height;
 
    cout << "Enter the distance from the base of the tree (in feet): ";
    cin >> distance;
 
    cout << "Enter the angle of elevation (in degrees): ";
    cin >> angleDegrees;
 
    // Convert degrees to radians
    angleRadians = angleDegrees / 57.2958;
 
    // Calculate height using trigonometry
    height = distance * tan(angleRadians);
 
    cout << "The height of the tree is: " << height << " feet" << endl;
 
    return 0;
}
// Formula: Height = Distance x tan(angle_in_radians)
// Conversion: radians = degrees / 57.2958
 