# include <iostream>
using namespace std;
int main(){
    char going;
    cout<<"are your friends going?(press Y for yes and N for no)";
    cin>>going;
    if(going == 'y'){
        cout<<"you are also going!";
    }
    if (going == 'n'){
        cout<<"you are not going!";
    }
}

