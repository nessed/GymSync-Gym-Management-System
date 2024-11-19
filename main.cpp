#include <iostream>
#include <string>
#include <fstream>
#define _TIME_ __TIME__  
#define _DATE_ __DATE__  
using namespace std;

void memberCheckIn(string memberid)

{
    ofstream file2("members_check_in_log.txt", ios::app);

    file2 << memberid << "  " << _TIME_ << "  " << _DATE_ << '\n';

    file2.close();
}

void memberCheckOut(string memberid)
{
    ofstream file3("members_check_out_log.txt", ios::app);

    file3 << memberid << "  " << _DATE_ << "  " << _TIME_ << '\n';

    file3.close();
}

string generateMemberId()
{
    string memberid;
    
    ifstream file("members.txt");
    
    if (file.peek() == EOF)
    {
        memberid = "10001";
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            memberid = line;
        }

        memberid = to_string(stoi(memberid) + 1);
    }
    file.close();

    return memberid;
}

void searchMember(string memberid)
{
    string name, contactno, membershipstartdate, membershiptype, activitystatus;
    ifstream file("members.txt");
    string currentline;
    do {
        getline(file, name);
        getline(file, contactno);
        getline(file, membershipstartdate);
        getline(file, membershiptype);
        getline(file, activitystatus);
        getline(file, currentline);
    } while (currentline != memberid);
    file.close();

    cout << "Name: " << name << endl;
    cout << "Contact Number: " << contactno << endl;
    cout << "Membership Start Date: " << membershipstartdate << endl;
    cout << "Membership Type: " << membershiptype << endl;
    cout << "Activity Status: " << activitystatus << endl;
}

void newRegistration()
{
    string name, contactno, membershipstartdate, membershiptype, memberid;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your contact number: ";
    cin >> contactno;
    membershipstartdate = _DATE_;
    cout << "The list of membership types and their corresponding monthly fee is mentioned below: " << endl;
    cout << "   1. Silver - Gym only ($10)" << endl;
    cout << "   2. Silver+ - Gym and Cardio only ($15.5)" << endl;
    cout << "   3. Gold - Gym only with a trainer ($30)" << endl;
    cout << "   4. Platinum - Gym, Cardio and a trainer ($32)" << endl;
    
    int userinput; 
    do {
    if ((userinput != 1) && (userinput != 2) && (userinput != 3) && (userinput != 4))
    {
        cout << "Enter number ranging from 1-4 only";
    }  
    cout << "Enter the number of membership you want (For Silver, press 1; For Silver+, press 2; For Gold; press 3; For Platinum, press 4)" << endl;
    cin >> userinput;
    } while ((userinput != 1) && (userinput != 2) && (userinput != 3) && (userinput != 4));

    memberid = generateMemberId();

    ofstream file("members.txt", ios::app);

    file << name + "\n";
    file << contactno + "\n";
    file << membershipstartdate + "\n";

    if (userinput == 1)
    {
        file << "Silver \n";
    }
    else if (userinput == 2)
    {
        file << "Silver+ \n";
    }
    else if (userinput == 3)
    {
        file << "Gold \n";
    }
    else
    {
        file << "Platinum \n";
    }

    file << "Active \n";
    file << memberid + "\n";
}

void memberTerminal()
{
    int userinput, userinput2;
    string memberid;
    do {
        cout << "Enter 1 if you are an existing member or enter 2 if you are a new member";
        cin >> userinput;
        if ((userinput != 1) && (userinput != 2))
        {
            cout << "Enter 1 or 2 only!";
        } 
    } while ((userinput != 1) && (userinput != 2));

    if (userinput == 2)
    {
        newRegistration();
    }
    else
    {
        do {
            cout << "Press 1 to check in or press 2 to check out: ";
            cin >> userinput2;
            if ((userinput2 != 1) && (userinput2 != 2))
            {
                cout << "Enter 1 or 2 only!";
            } 
        } while ((userinput2 != 1) && (userinput2 != 2));

        cout << "Enter your Member ID: ";
        cin >> memberid;
        
        if (userinput2 == 1)
        {
            memberCheckIn(memberid);
        }
        else
        {
            memberCheckOut(memberid);
        }
    }
}

void managerTerminal()
{
    int actioninput;
    int attempts = 1;
    string password;
    string correctpassword = "FitnessGym123";
    bool access = false;
    
    cout << "Enter password to access Manager terminal. You only have four tries to enter correct password." << endl;
    do {
    cout << "Password: ";
    cin >> password;
    if (password == correctpassword)
    {
        access = true;
        cout << "Access Granted!";
    }
    else
    {
        cout << "Wrong password. Please Try again!";
    }
    } while (attempts <= 4 && !access);

    if (!access)
    {
        cout << "Access Denied. " << endl << "Restarting the system........" << endl << endl << endl;
    }
    else
    {
        cout << "Select any action you want from the list below: " << endl;
        cout << "   1, Update Member Information" << endl;
        cout << "   2, Search Member Details" << endl;
        cout << "   3, Report Generation" << endl;

        do {
            cout << "Enter 1 to Update Member Information; Enter 2 to Search for Member Details; Enter 3 to Generate Report: ";
            cin >> actioninput;
            if ((actioninput != 1) && (actioninput != 2) && (actioninput != 3))
            {
                cout << "Enter 1 or 2 or 3 only" << endl;
            }
        } while ((actioninput != 1) && (actioninput != 2) && (actioninput != 3));

        if (actioninput == 2)
        {
            string memberid;

            cout << "Enter the ID of member you want to search the information from: ";
            cin >> memberid;

            searchMember(memberid);
        }
    }
}

int main()
{
    int userinput, userinput2;
    cout << "Welcome to Gym Management System!" << endl;
    do {
        cout << "Enter 1 if you are a Member or enter 2 if you are a Manager: ";
        cin >> userinput;
        if ((userinput != 1) && (userinput != 2))
        {
            cout << "Enter 1 or 2 only!";
        } } while ((userinput != 1) && (userinput != 2));
    if (userinput == 1)
    {
        memberTerminal();
    }
    else
    {
        managerTerminal();
    }

    return 0;
}