#include<iostream>
using namespace std;

int main()
{
    int num_prod;
    cout<<"Enter number of products: ";cin>>num_prod;
    string fruits[num_prod];
    float prices[num_prod];
    int quantity[num_prod];

    for (int i = 0; i < num_prod; i++)
    {
        cout<<"Enter name of product: ";cin>>fruits[i];
        cout<<"Enter price of "<<fruits[i]<<" :";cin>>prices[i];
        cout<<"Enter quantity of "<<fruits[i]<<" :";cin>>quantity[i];
    }

    cout<<"Product Inventory Report\n";
    cout<<"------------------------\n";
    
    for (int i=0;i<num_prod;i++)
    {
        cout<<fruits[i]<<" : $"<<prices[i]<<", "<<quantity[i]<<" in stock, Total Value: $"<<prices[i]*quantity[i]<<endl;
    }
    return 0;
}