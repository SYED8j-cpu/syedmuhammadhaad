#include<iostream>
using namespace std;

int main()
{
    int num_flight;
    cout<<"Enter number of flights: ";cin>>num_flight;
    int flight_number[num_flight];
    string destination[num_flight];
    int seats_available[num_flight];

    for (int i = 0; i < num_flight; i++)
    {
        cout<<"\nEnter flight number for flight "<<i+1<<": ";cin>>flight_number[i];
        cout<<"Enter destination for flight "<<flight_number[i]<<" :";cin>>destination[i];
        cout<<"Enter seats available for "<<flight_number[i]<<" :";cin>>seats_available[i];
    }

    cout<<"\nFlight Information\n";
    cout<<"------------------------\n";
    
    for (int i=0;i<num_flight;i++)
    {
        cout<<"Flight "<<flight_number[i]<<" to "<<destination[i]<<" has "<<seats_available[i]<<" seats available."<<endl;
    }
    cout<<"\nFlights with less than 5 seats\n";
    cout<<"-------------------------------\n";

    bool flight_with_less_than_5_seats = false;
    for (int i = 0; i < num_flight; i++)
    {
        if(seats_available[i]<5)
        {
            cout<<"Flight "<<flight_number[i]<<" to "<<destination[i]<<" has "<<seats_available[i]<<" seats left!"<<endl;
            flight_with_less_than_5_seats = true;
        }
    }
    if(!flight_with_less_than_5_seats)
    {
         cout<<"No flight with less than 5 seats";
    }
    
    return 0;
}