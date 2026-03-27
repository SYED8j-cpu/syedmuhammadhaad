#include<iostream>
using namespace std;

int main()
{
    int n = 0;
    string book[100];
    bool borrowed[100] = {false};
    string name;

    while(true)
    {
        cout<<"\nLIBRARY MANAGEMENT SYSTEM\n";
        cout<<"1. ADD BOOKS\n";
        cout<<"2. VIEW BOOKS\n";
        cout<<"3. BORROW BOOKS\n";
        cout<<"4. RETURN BOOKS\n";
        cout<<"5. EXIT\n";

        int choice;
        cout<<"Enter the choice(1-5): ";
        cin >> choice;

        if(choice==1)
        {
            cout<<"How many books you want to enter: ";
            cin >> n;
            cin.ignore();

            cout<<"Enter names of "<<n<<" books:\n";
            for(int i=0 ; i < n ; i++)
            {
                getline(cin, book[i]);
                borrowed[i] = false;
            }
        }
        
        else if(choice==2)
        {
            if(n==0)
            {
                cout<<"No books added yet\n";
                continue;
            }

            cout<<"Books in library:\n";
            for(int i=0; i<n; i++)
            {
                cout<<book[i];

                if(borrowed[i])
                    cout<<" (Borrowed)";
                else
                    cout<<" (Available)";

                cout<<endl;
            }
        }

        else if(choice==3)
        {
            cout<<"Enter book name to borrow: ";
            cin.ignore();
            getline(cin, name);

            bool found=false;

            for(int i=0 ; i< n ; i++)
            {
                if(book[i]==name)
                {
                    if(borrowed[i])
                    {
                        cout<<"Book already borrowed\n";
                    }
                    else
                    {
                        borrowed[i] = true;
                        cout<<"You borrowed "<<name<<endl;
                    }
                    found=true;
                    break;
                }
            }

            if(!found)
            {
                cout<<"Book not found\n";
            }
        }

        else if(choice==4)
        {
            cout<<"Enter book name to return: ";
            cin.ignore();
            getline(cin, name);

            bool found=false;

            for(int i=0 ; i< n ; i++)
            {
                if(book[i]==name)
                {
                    if(!borrowed[i])
                    {
                        cout<<"This book was not borrowed\n";
                    }
                    else
                    {
                        borrowed[i] = false;
                        cout<<"Book returned successfully\n";
                    }
                    found=true;
                    break;
                }
            }

            if(!found)
            {
                cout<<"Book not found\n";
            }
        }

        else if(choice==5)
        {
            cout<<"THANKS FOR VISITING OUR LIBRARY\n";
            break;
        }

        else 
        {
            cout<<"Invalid choice.\n";
        }
    }
}