#include<iostream>
using namespace std;

int main()
{
    int num_students;
    cout<<"Enter number of students: ";cin>>num_students;
    string array[num_students];
    cout<<"Enter names of "<<num_students<<" students: \n";
    for (int idx = 0; idx < num_students; idx++)
    {
        cin>>array[idx];
    }
    
    for (int i=0;i<num_students-1;i++)
    {
        for (int j = i+1; j < num_students; j++)
        {
            if(array[i]>array[j])
            {
                string temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    cout<<"Student names in alphabetic order:\n";
    for(int i = 0; i < num_students; i++)
    {
        cout<<array[i]<<" \n";
    }
    return 0;
}