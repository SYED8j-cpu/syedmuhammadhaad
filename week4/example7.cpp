# include <iostream>
using namespace std;
int main(){
    string name;
    cout<<"please enter your name: ";
    cin>>name;
    if(name == "ali"){
        cout<< "welcome "<<name<<endl;
    }
    if(name != "ali"){
        cout<<"TRY AGAIN!";
    }
}