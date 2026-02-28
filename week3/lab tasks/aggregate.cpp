# include <iostream>
using namespace std;
main()
{
cout<<"enter matric marks:"<<endl;
int matric;
cin>>matric;
cout<<"enter inter marks:"<<endl;
int inter;
cin>>inter;
cout<<"enter ecat marks:"<<endl;
int ecat;
cin>>ecat;
float aggregate;
aggregate=(matric*10)/1100+(inter*40)/1200+(ecat*50)/400;
cout<<"your aggregate:"<<aggregate<<"%";
}