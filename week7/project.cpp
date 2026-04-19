#include <iostream>
#include <string>
#include <conio.h>

using namespace std;
int main()
{
    int total_students = 1000; // total size
    int index = 7;

    // data structures
    string nameArray[total_students] = {"ali", "ammar", "sara", "usman", "hira", "bilal", "zara"};
    int ageArray[total_students] = {20, 21, 19, 22, 20, 21, 19};
    float matricArray[total_students] = {1050, 850, 950, 900, 1000, 880, 920};
    float interArray[total_students] = {980, 850, 900, 870, 960, 820, 890};
    float ecats[total_students] = {300, 250, 280, 260, 310, 240, 270};
    string pref1Array[total_students] = {"cs", "ce", "ee", "cs", "ce", "ee", "cs"};
    string pref2Array[total_students] = {"ce", "cs", "cs", "ee", "cs", "cs", "ce"};
    string pref3Array[total_students] = {"ee", "ce", "ce", "ce", "ee", "ce", "ee"};
    float aggriArray[total_students] = {0};
    while (true)
    {
        // main heder for ums
        system("cls");
        cout << "-----------------------------------" << endl;
        cout << "    University Management System   " << endl;
        cout << "-----------------------------------" << endl;

        cout << "user menu" << endl;
        cout << "1 admin" << endl;
        cout << "2 student" << endl;
        cout << "3 to exit" << endl;
        cout << "choose option" << endl;
        string useroption;
        cin >> useroption;

        cout << "you choose " << useroption << endl;
        if (useroption == "1")
        {
            // write code for admin
            int countattempt = 0;
            for (int i = 0; i < 3; i++)
            {
                system("cls");
                cout << " admin menu : login attempt " << i + 1 << endl;
                cout << "enter username:" << endl;
                string username;
                cin >> username;
                cout << "enter password:" << endl;
                string password;
                cin >> password;
                if (username == "admin" && password == "admin123")
                {
                    cout << "login successful" << endl;
                    while (true)
                    {
                        system("cls");
                        cout << "1show all students data" << endl;
                        cout << "2 search student data by name" << endl;
                        cout << "3 UPDATE student record" << endl;
                        cout << "4 generate merit list" << endl;
                        cout << "5 delete record by name" << endl;
                        cout << "6 logout" << endl;
                        cout << "choose option" << endl;
                        int adminoption;
                        cin >> adminoption;
                        if (adminoption == 1)
                        {
                            cout << "name\tage\tmatric\tinter\tecat\tpref1\tpref2\tpref3" << endl;
                            for (int i = 0; i < index; i++)
                            {
                                if (nameArray[i] != "")
                                {
                                    cout << nameArray[i] << "\t" << ageArray[i] << "\t" << matricArray[i] << "\t" << interArray[i] << "\t" << ecats[i] << "\t" << pref1Array[i] << "\t" << pref2Array[i] << "\t" << pref3Array[i] << endl;
                                }
                            }
                        }
                        else if (adminoption == 2)
                        {
                            // find student  by name
                            cout << "enter name of student you want to search" << endl;
                            string name;
                            cin >> name;
                            bool found = false;
                            for (int i = 0; i < index; i++)
                            {
                                if (nameArray[i] == name)
                                {
                                    cout << "name\tage\tmatric\tinter\tecat\tpref1\tpref2\tpref3" << endl;
                                    cout << nameArray[i] << "\t" << ageArray[i] << "\t" << matricArray[i] << "\t" << interArray[i] << "\t" << ecats[i] << "\t" << pref1Array[i] << "\t" << pref2Array[i] << "\t" << pref3Array[i] << endl;
                                    found = true;
                                }
                            }
                            if (!found)
                            {
                                cout << "student not found" << name << endl;
                            }
                            else
                            {
                                cout << "student record has been found" << name << endl;
                            }
                        }
                        else if (adminoption == 3)
                        { // update student record
                            cout << "enter name of student you want to search" << endl;
                            string name;
                            cin >> name;
                            bool found = false;
                            int Foundindex = -1;
                            for (int i = 0; i < index; i++)
                            {
                                if (nameArray[i] == name)
                                {
                                    cout << "name\tage\tmatric\tinter\tecat\tpref1\tpref2\tpref3" << endl;
                                    cout << nameArray[i] << "\t" << ageArray[i] << "\t" << matricArray[i] << "\t" << interArray[i] << "\t" << ecats[i] << "\t" << pref1Array[i] << "\t" << pref2Array[i] << "\t" << pref3Array[i] << endl;
                                    found = true;
                                    Foundindex = i;
                                }
                            }
                            if (found == false)
                            {
                                cout << "student not found" << name << endl;
                                ;
                            }
                            else
                            {
                                cout << "----------old record----------" << endl;
                                cout << "enter new record for updating" << endl;
                                cout << "enter your name" << endl;
                                string name;
                                cin >> name;
                                cout << "enter your age" << endl;
                                int age;
                                cin >> age;
                                cout << "enter your matric marks" << endl;
                                float matric;
                                cin >> matric;
                                cout << "enter your inter marks" << endl;
                                float inter;
                                cin >> inter;
                                cout << "enter your ecat marks" << endl;
                                float ecat;
                                cin >> ecat;
                                cout << "enter cs,ce,ee as your prefernces" << endl;
                                cout << "enter your 1st prefernce:" << endl;
                                string pref1;
                                cin >> pref1;
                                cout << "enter your 2nd prefernce:" << endl;
                                string pref2;
                                cin >> pref2;
                                cout << "enter your 3rd prefernce:" << endl;
                                string pref3;
                                cin >> pref3;

                                nameArray[Foundindex] = name;
                                ageArray[Foundindex] = age;
                                matricArray[Foundindex] = matric;
                                interArray[Foundindex] = inter;
                                ecats[Foundindex] = ecat;
                                pref1Array[Foundindex] = pref1;
                                pref2Array[Foundindex] = pref2;
                                pref3Array[Foundindex] = pref3;
                            }
                        }

                        else if (adminoption == 4)
                        {
                            // generate merit list
                            for (int i = 0; i < index; i++)
                            {
                                float aggregate = (matricArray[i] / 1100) * 100 * 0.10 + (interArray[i] / 1100) * 100 * 0.40 + (ecats[i] / 400) * 100 * 0.50;
                                aggriArray[i] = aggregate;
                            }
                            // sorting the data on the basis of aggregate
                            for (int i = 0; i < index; i++)
                            {
                                for (int j = 1; j < index; j++)
                                {
                                    if (aggriArray[j] < aggriArray[j])
                                    {
                                        // swaping of name
                                        string temp = nameArray[i];
                                        nameArray[i] = nameArray[j];
                                        nameArray[j] = temp;

                                        // swaping of age
                                        int tempAge = ageArray[i];
                                        ageArray[i] = ageArray[j];
                                        ageArray[j] = tempAge;

                                        // swaping of matric
                                        float tempMatric = matricArray[i];
                                        matricArray[i] = matricArray[j];
                                        matricArray[j] = tempMatric;

                                        // swaping of inter
                                        float tempInter = interArray[i];
                                        interArray[i] = interArray[j];
                                        interArray[j] = tempInter;

                                        // swaping of ecat
                                        float tempEcat = ecats[i];
                                        ecats[i] = ecats[j];
                                        ecats[j] = tempEcat;

                                        // swaping of pref1
                                        string tempPref1 = pref1Array[i];
                                        pref1Array[i] = pref1Array[j];
                                        pref1Array[j] = tempPref1;

                                        // swaping of pref2
                                        string tempPref2 = pref2Array[i];
                                        pref2Array[i] = pref2Array[j];
                                        pref2Array[j] = tempPref2;

                                        // swaping of pref3
                                        string tempPref3 = pref3Array[i];
                                        pref3Array[i] = pref3Array[j];
                                        pref3Array[j] = tempPref3;

                                        // swaping of aggregate
                                        float tempAggregate = aggriArray[i];
                                        aggriArray[i] = aggriArray[j];
                                        aggriArray[j] = tempAggregate;
                                    }
                                }
                            }
                            // code to display all data with aggregate
                            cout << "name\tage\taggregate" << endl;
                            for (int i = 0; i < index; i++)
                            {
                                if (nameArray[i] != "")
                                {
                                    cout << nameArray[i] << "\t" << ageArray[i] << "\t" << aggriArray[i] << endl;
                                }
                            }
                            // admit students into disciplines on the basis of their prefernces and aggregate
                        }
                        else if (adminoption == 5)
                        {
                            // delete record by name
                            cout << "enter name of student you want to delete" << endl;
                            string name;
                            cin >> name;
                            bool found = false;
                            int Foundindex = -1;
                            for (int i = 0; i < index; i++)
                            {
                                if (nameArray[i] == name)
                                {
                                    cout << "name\tage\tmatric\tinter\tecat\tpref1\tpref2\tpref3" << endl;
                                    cout << nameArray[i] << "\t" << ageArray[i] << "\t" << matricArray[i] << "\t" << interArray[i] << "\t" << ecats[i] << "\t" << pref1Array[i] << "\t" << pref2Array[i] << "\t" << pref3Array[i] << endl;
                                    found = true;
                                    Foundindex = i;
                                }
                            }
                            if (found == true)
                            {
                                nameArray[Foundindex] = "";
                                ageArray[Foundindex] = 0;
                                matricArray[Foundindex] = 0;
                                interArray[Foundindex] = 0;
                                ecats[Foundindex] = 0;
                                pref1Array[Foundindex] = "";
                                pref2Array[Foundindex] = "";
                                pref3Array[Foundindex] = "";
                                cout << "student record has been deleted" << name << endl;
                            }
                            else
                            {
                                cout << "student not found" << name << endl;
                            }
                        }
                        else if (adminoption == 6)
                        {
                            break;
                        }
                        else
                        {
                            cout << "you entered the wrong option" << endl;
                        }
                        cout << "press any key to continue" << endl;
                        getch();
                    }

                    getch();
                    break;
                }
                else
                {
                    cout << "invalid username or password" << endl;
                }
                cout << "press any key to continue" << endl;
                getch();
            }
        }
        else if (useroption == "2")
        {
            // write code for student
            cout << "welcome to ums student menu" << endl;
            cout << "enter your name" << endl;
            string name;
            cin >> name;
            cout << "enter your age" << endl;
            int age;
            cin >> age;
            cout << "enter your matric marks" << endl;
            float matric;
            cin >> matric;
            cout << "enter your inter marks" << endl;
            float inter;
            cin >> inter;
            cout << "enter your ecat marks" << endl;
            float ecat;
            cin >> ecat;
            cout << "enter cs,ce,ee as your prefernces" << endl;
            cout << "enter your 1st prefernce:" << endl;
            string pref1;
            cin >> pref1;
            cout << "enter your 2nd prefernce:" << endl;
            string pref2;
            cin >> pref2;
            cout << "enter your 3rd prefernce:" << endl;
            string pref3;
            cin >> pref3;

            nameArray[index] = name;
            ageArray[index] = age;
            matricArray[index] = matric;
            interArray[index] = inter;
            ecats[index] = ecat;
            pref1Array[index] = pref1;
            pref2Array[index] = pref2;
            pref3Array[index] = pref3;
            index = index + 1;
            cout << "your data has been recorded" << endl;
            cout << "press any key to continue" << endl;
            getch();
        }
        else if (useroption == "3")
        {
            break;
        }
        else
        {
            cout << "you entered the wrong option" << endl;
        }
    } // end of our main while loop
    cout << endl
         << "thank you for using this software" << endl;
}