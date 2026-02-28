# include <iostream>
using namespace std;
int main()
{
cout<< "enter name:" <<endl;
string movie;
cin>>movie;
cout<<"enter price of an adult ticket:"<<endl;
int adult;
cin>>adult;
cout<<"enter price of child ticket:"<<endl;
int child;
cin>>child;
cout<<"enter number of adult tickets sold:"<<endl;
int sold;
cin>>sold;
cout<<"number of children tickets sold:"<<endl;
int children;
cin>>children;
cout<<"percentage of total money to donate to charity:"<<endl;
double charity;
cin>>charity;
double total;
total=(adult*sold)+(child*children);
double percentage;
percentage=total*(charity/100);
double remaining;
remaining=total-percentage;
cout<<"enter the movie name:"<<movie<<endl;
cout<<"enter the adult ticket price:"<<adult<<"$"<<endl;
cout<<"enter the child ticket price:"<<child<<"$"<<endl;
cout<<"enter number of adult ticket sold:"<<sold<<endl;
cout<<"enter number of child ticket sold:"<<children<<endl;
cout<<"enter donation tp charity:"<<charity<<"%"<<endl;
cout<<"-----------------------------------"<<endl;
cout<<"movie:"<<movie<<endl;
cout<<"total amount generated from ticket sales:"<<total<<"$"<<endl;
cout<<"donation to charity:"<<percentage<<"$"<<endl;
cout<<"remaining amount after donation:"<<remaining<<"$"<<endl;
}
