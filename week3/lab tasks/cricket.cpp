# include <iostream>
using namespace std;
int main()
{
cout<<"enter the number of wins:"<<endl;
int wins;
cin>>wins;
cout<<"enter the number of draws:"<<endl;
int draws;
cin>>draws;
cout<<"enter the number of losses:"<<endl;
int losses;
cin>>losses;
int points;
points=(wins*3)+(draws*1)+(losses*0);
cout<<"wins:"<<wins;
cout<<"draws:"<<draws;
cout<<"losses:"<<losses;
cout<<"points:"<<points;
}