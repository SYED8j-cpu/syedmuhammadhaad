# include <iostream>
using namespace std;
int main()
{
cout<<"number of square meters you can paint:"<<endl;
int n;
cin>>n;
cout<<"width of the single wall:"<<endl;
int w;
cin>>w;
cout<<"height of a single wall:"<<endl;
int h;
cin>>h;
int total;
total=n/(w*h);
cout<<"number of square meters you can paint:"<<n<<endl;
cout<<"width of the single wall:"<<w<<endl;
cout<<"height of the single wall:"<<h<<endl;
cout<<"number of walls you can paint:"<<total<<endl;
}