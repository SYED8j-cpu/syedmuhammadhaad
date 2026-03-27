#include<iostream>
using namespace std;

int main()
{
    int choice = 0;
    string name[3] , course[3];
    int age[3];
    int i1=0,i2=0;
    string username[3];
    int password[3];
    for(int i = 0; i < 3; i++)
    {
        cout<<"Enter username: ";cin>>username[i];

        cout<<"Enter password: ";cin>>password[i];

        if(username[i] == "admin" && password[i] == 1234)
        {
            cout<<"Login Successful\n";

            while(choice != 5)
            {
                cout<<"--------University Menu---------\n";
                cout<<"1--> Add Student\n";
                cout<<"2--> View Student\n";
                cout<<"3--> Add Course\n";
                cout<<"4--> View Course\n";
                cout<<"5--> Exit\n";
                cout<<"Your Choice: ";
                cin>>choice;

                if(choice == 1)
                {
                    if(i1 < 3)
                    {
                        cout<<"Enter name: ";
                        cin>>name[i1];

                        cout<<"Enter age: ";
                        cin>>age[i1];

                        i1++;
                        cout<<"Student added successfully\n";
                    }
                    else
                    {
                        cout<<"Student limit reached\n";
                    }
                }
                else if(choice == 2)
                {
                    for (int c=0;c<i1;c++)
                    {
                        cout<<"Student "<<c+1<<": "<<name[c]<<" Age: "<<age[c]<<endl;
                    }
                    
                }
                else if(choice == 3)
                {
                    if(i2 < 3)
                    {
                        cout<<"Enter course name: ";
                        cin>>course[i2];

                        i2++;
                        cout<<"Course added successfully\n";
                    }
                    else
                    {
                        cout<<"Course limit reached\n";
                    }
                }
                else if (choice == 4)
                {
                    for (int d=0;d<i2;d++)
                    {
                        cout<<"Course "<<d+1<<": "<<course[d]<<endl;
                    }
                }
                
                else if(choice == 5)
                {
                    cout<<"Exiting program.\n";
                }
                else
                {
                    cout<<"Enter correct choice.\n";
                }
            }

            break; 
        }
        else
        {
            cout<<"Wrong username or password\n";
        }
    }
    return 0;
}