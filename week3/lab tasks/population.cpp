# include <iostream>
using namespace std;
int main()
{
cout<<"enter current world population:"<<endl;
int population;
cin>>population;
cout<<"enter monthly birth rate:"<<endl;
int birthrate;
cin>>birthrate;
int people;
people=population+(360*birthrate);
cout<<"world population:"<<population<<endl;
cout<<"birth rate:"<<birthrate<<endl;
cout<<"population in three decades="<<people<<endl;
}