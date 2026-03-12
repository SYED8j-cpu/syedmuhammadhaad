# include <iostream>
using namespace std;
int maain()
{
    string my_password,user_enter;
    my_password = "pass@1231";
    cout<<"enter the password:";
    cin>>user_enter;
    if(user_enter == my_password){
        cout<<"wow ! you have cracked the code!";        
    }
    else{
        cout<<"it is not that simple,TRY AGAIN";
     }
}