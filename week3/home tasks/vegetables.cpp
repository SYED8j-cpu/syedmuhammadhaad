# include <iostream>
using namespace std;
int main()
{
cout<<"enter vegetables price:"<<endl;
float n;
cin>>n;
cout<<"enter fruit price:"<<endl;
float m;
cin>>m;
cout<<"enter vegetables per kilogram:"<<endl;
float kg;
cin>>kg;
cout<<"enter fruit per kilogram:"<<endl;
float kgs;
cin>>kgs;
float coins;
coins=(n*kg)+(m*kgs);
float rps;
rps=(coins/1.94);
cout<<"enter vegetables price per kilogram(in coins):"<<n<<endl;
cout<<"enter fruit price per kilogram(in coins):"<<m<<endl;
cout<<"enter total kilograms of vegetables:"<<kg<<endl;
cout<<"enter total kilograms of fruits:"<<kgs<<endl;
cout<<"total earning in rupees(in rps):"<<rps<<endl;
}

