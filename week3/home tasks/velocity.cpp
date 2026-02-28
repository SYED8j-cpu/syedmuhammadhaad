# include <iostream>
using namespace std;
int main()
{
cout<<"enter initial velocity:"<<endl;
int velocity;
cin>>velocity;
cout<<"enter acceleration:"<<endl;
int acceleration;
cin>>acceleration;
cout<<"enter time:"<<endl;
int time;
cin>>time;
int finalv;
finalv=(acceleration*time)+velocity;
cout<<"enter initial velocity:"<<velocity<<endl;
cout<<"enter accelaration:"<<acceleration<<endl;
cout<<"enter time:"<<time<<endl;
cout<<"final velocity will be="<<finalv<<endl;
}