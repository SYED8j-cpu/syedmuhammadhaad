#include <iostream>
using namespace std;
int main()
{
    double totalAmount, discount, finalAmount;
    cout << "enter the bill amount:";
    cin >> totalAmount;
    if (totalAmount <= 5000)
    {
        discount = totalAmount * 0.05;
    }
    else
    {
        discount = totalAmount * 0.10;
    }
    finalAmount = totalAmount - discount;
    cout << "your discounted bill is:" << finalAmount << endl;
}