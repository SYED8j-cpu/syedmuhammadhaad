#include <iostream>
using namespace std;
int main()
{
    string country;
    double ticketPrice, discount, discountedPrice;
    cout << "Enter Country: ";
    cin >> country;
    cout << "Enter Ticket Price: ";
    cin >> ticketPrice;
    if (country == "Ireland")
    {
        discount = ticketPrice * 0.10;
    }
    else
    {
        discount = ticketPrice * 0.05;
    }
    discountedPrice = ticketPrice - discount;
    cout << "Discounted Price: " << discountedPrice << endl;
}
