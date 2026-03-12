#include <iostream>
using namespace std;

int main()
{
    int red, white, tulip;
    double originalPrice, finalPrice;
    cout << "Enter number of Red Roses: ";
    cin >> red;
    cout << "Enter number of White Roses: ";
    cin >> white;
    cout << "Enter number of Tulips: ";
    cin >> tulip;
    originalPrice = (red * 2.00) + (white * 4.10) + (tulip * 2.50);

    cout << "Original Price: " << originalPrice << endl;
    if (originalPrice > 200)
    {
        finalPrice = originalPrice - (originalPrice * 0.20);
        cout << "Price after Discount: " << finalPrice << endl;
    }
    else
    {
        cout << "No discount applied. Total: " << originalPrice << endl;
    }
}
