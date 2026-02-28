# include <iostream>
using namespace std;
int main()
{
cout << "weight of fertilizer:"<<endl;
double weight;
cin>>weight;
cout << "cost of bag:"<<endl;
double cost;
cin>>cost;
cout << "size of area bag can cover:" << endl;
double size;
cin>>size;
int price1;
price1=cost/weight;
int price2;
price2=cost/size;
cout<<" weight is:"<<weight<<endl;
cout<<" cost is:"<<cost<<"$"<<endl;
cout<<"size is:"<<size<<endl;
cout<<"price of fertilizer for each pound:"<<price1<<"$"<<endl;
cout<<"cost of using fertilizer for each square foot of garden:"<<price2<<"$"<<endl;
}
