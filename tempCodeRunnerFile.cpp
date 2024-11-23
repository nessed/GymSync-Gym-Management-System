#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#define TIME __TIME__
#define DATE __DATE__
using namespace std;

class member
{
private:
    string name, contactno, membershiptype, membershipstartdate, membershipduration, activitystatus, memberid;
    vector<string> checktype;
    vector<string> attendancedate;
    vector<string> attendancetime;

public:
    member(string name, string contactno, string membershipstartdate, string membershiptype, string membershipduration, string activitystatus, string memberid) : name(name), contactno(contactno), membershipstartdate(membershipstartdate), membershiptype(membershiptype), membershipduration(membershipduration), activitystatus(activitystatus), memberid(memberid) {}

    void setName(string namep)
    {
        name = namep;
    }
    void setContactNo(string contactnop)
    {
        contactno = contactnop;
    }
    void setMembershipStartDate(string membershipstartdatep)
    {
        membershipstartdate = membershipstartdatep;
    }
    void setMembershipType(string membershiptypep)
    {
        membershiptype = membershiptypep;
    }
    void setMembershipDuration(string membershipdurationp)
    {
        membershipduration = membershipdurationp;
    }
    void setActivityStatus(string activitystatusp)
    {
        activitystatus = activitystatusp;
    }
    void setMemberId(string memberidp)
    {
        memberid = memberidp;
    }
    void setCheckType(string checktypep)
    {
        checktype.push_back(checktypep);
    }
    void setAttendanceDate(string datep)
    {
        attendancedate.push_back(datep);
    }
    void setAttendanceTime(string timep)
    {
        attendancetime.push_back(timep);
    }

    string getName()
    {
        return name;
    }
    string getContactNo()
    {
        return contactno;
    }
    string getMembershipStartDate()
    {
        return membershipstartdate;
    }
    string getMembershipType()
    {
        return membershiptype;
    }
    string getMembershipDuration()
    {
        return membershipduration;
    }
    string getActivityStatus()
    {
        return activitystatus;
    }
    string getMemberId()
    {
        return memberid;
    }
    string getCheckType(int index)
    {
        return checktype[index];
    }
    string getAttendanceDate(int index)
    {
        return attendancedate[index];
    }
    string getAttendanceTime(int index)
    {
        return attendancetime[index];
    }

    int getCheckTypeSize()
    {
        return checktype.size() - 1; 
    }
    int getAttendanceDateSize()
    {
        return attendancedate.size() - 1; 
    }
    int getAttendanceTimeSize()
    {
        return attendancetime.size() - 1; 
    }
};

ofstream file("members.txt", ios::app);

ofstream file2("attendance.txt", ios::app);

vector<member> members;

void readMainFile()
{
    ifstream file("members.txt");
    if (file.is_open())
    {
        string fileline, name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid;
        while (getline(file, name))
        {
            getline(file, contactno);
            getline(file, membershipstartdate);
            getline(file, membershiptype);
            getline(file, membershipduration);
            getline(file, activitystatus);
            getline(file, memberid);

            members.push_back(member(name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid));
        }

        file.close();
    }
    else
    {
        cout << "Error: File containing member details does not exist!" << endl;
        cout << "Exiting Program.......";
    }
}

void writeMainFile()
{
    ofstream file("members.txt", ios::app);
    if (file.is_open())
    {
        string fileline, name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid;
        int lastindex = members.size() - 1;

        for (int index = 0; index <= lastindex; ++index)
        {
            file << members[index].getName() + '\n';
            file << members[index].getContactNo() + '\n';
            file << members[index].getMembershipStartDate() + '\n';
            file << members[index].getMembershipType() + '\n';
            file << members[index].getMembershipDuration() + '\n';
            file << members[index].getActivityStatus() + '\n';
            file << members[index].getMemberId() + '\n';

            file.close();
        }
    }
    else
    {
        cout << "Error: Cannot write members data to the Main file" << endl;
        cout << "Exiting the Program......";
    }
}

void readAttendanceFile()
{
    ifstream file2("attendance.txt");

    if (file2.is_open())
    {
        string checktype, attendancedate, attendancetime, memberid;

        while (getline(file2, checktype))
        {
            getline(file2, attendancedate);
            getline(file2, attendancetime);
            getline(file2, memberid);

            bool recordfound = false;
            int index = 0;
            int updateindex;
            int lastindex = members.size() -  1;

            do
            {
                if (members[index].getMemberId() == memberid)
                {
                    recordfound = true;
                }
                ++index;
            } while (!recordfound);

            members[index].setCheckType(checktype);
            members[index].setAttendanceDate(attendancedate);
            members[index].setAttendanceTime(attendancetime);
        }
        
        file2.close();
    }
    else
    {
        cout << "Error: Cannot open attendance file!" << endl;
        cout << "Exiting Program......";
    }
}

void writeAttendanceFile()
{
    ofstream file2("attendance.txt");
    
    if (file2.is_open())
    {
        int lastindex1 = members.size() - 1;
        int index1 = 0;

        while (index1 <= lastindex1)
        {
            int lastindex2, attendancetimeindex, checktypeindex, attendancedateindex;
            int index2 = 0;
            string checktype, attendancetime, attendancedate, memberid;

            lastindex2 = members[lastindex1].getAttendanceDateSize();

            memberid = members[index1].getMemberId();
            while (index2 <= lastindex2)
            {
                checktype = members[index1].getCheckType(index2);
                attendancedate = members[index1].getAttendanceDate(index2);
                attendancetime = members[index1].getAttendanceTime(index2);

                file << checktype + '\n';
                file << attendancedate + '\n';
                file << attendancetime + '\n';
                file << memberid + '\n';

                ++index2;
            }
            ++index1;
        }

        file2.close();
    }
    else {
        cout << "Cannot open attendance file for writing" << endl;
        cout << "Exiting System......";
    }
}

void memberCheckIn(string memberid)
{
    string time, date;
    time = __TIME__;
    date = __DATE__;

    bool recordfound = false;
    int index = 0;
    int updateindex;
    do
    {
        if (members[index].getMemberId() == memberid)
        {
            recordfound = true;
            updateindex = index;
        }
        ++index;
    } while (!recordfound);

    members[updateindex].setCheckType("Check-In");
    members[updateindex].setAttendanceDate(date);
    members[updateindex].setAttendanceTime(time);
}

void memberCheckOut(string memberid)
{
    string time, date;
    time = __TIME__;
    date = __DATE__;

    bool recordfound = false;
    int index = 0;
    int updateindex;
    do
    {
        if (members[index].getMemberId() == memberid)
        {
            recordfound = true;
            updateindex = index;
        }
        ++index;
    } while (!recordfound);

    members[updateindex].setCheckType("Check-Out");
    members[updateindex].setAttendanceDate(date);
    members[updateindex].setAttendanceTime(time);
}

string generateMemberId()
{
    string memberid;

    if (!members.empty())
    {
        int index = members.size() - 1;
        memberid = to_string(stoi(members[index].getMemberId()) + 1);
    }
    else
    {
        memberid = "10001";
    }

    return memberid;
}

void newRegistration()
{
    string name, contactno, membershipstartdate, membershipduration, membershiptype, activitystatus, memberid;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your contact number: ";
    cin >> contactno;
    membershipstartdate = __DATE__;

    cout << "The list of membership types and their corresponding monthly fee is mentioned below: " << endl;
    cout << "   1. Silver - Gym only (monthly: $10, yearly: $110)" << endl;
    cout << "   2. Silver+ - Gym and Cardio only (monthly: $15.5, yearly: $160)" << endl;
    cout << "   3. Gold - Gym only with a trainer (monthly: $30, yearly: $300)" << endl;
    cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl << endl;

    int userinput1, userinput2;

    do
    {
        if ((userinput2 != 1) && (userinput2 != 2) && (userinput2 != 3) && (userinput2 != 4))
        {
            cout << "Enter number ranging from 1-4 only";
        }
        cout << "Enter the number of membership you want (For Silver, press 1; For Silver+, press 2; For Gold; press 3; For Platinum, press 4)" << endl;
        cin >> userinput2;
    } while ((userinput2 != 1) && (userinput2 != 2) && (userinput2 != 3) && (userinput2 != 4));

    if (userinput2 == 1)
    {
        membershiptype = "Silver";
    }
    else if (userinput2 == 2)
    {
        membershiptype = "Silver+";
    }
    else if (userinput2 == 3)
    {
        membershiptype = "Gold";
    }
    else
    {
        membershiptype = "Platinum";
    }

    cout << "Membership Duration: " << endl;
    do
    {
        if ((userinput1 != 1) && (userinput1 != 2))
        {
            cout << "Enter 1 or 2 only!" << endl;
        }
        cout << "Enter 1 if you want monthly membership or enter 2 if you want yearly membership: " << endl;
        cin >> userinput1;
    } while ((userinput1 != 1) && (userinput1 != 2));

    if (userinput1 == 1)
    {
        membershipduration = "Monthly";
    }
    else
    {
        membershipduration = "Yearly";
    }

    memberid = generateMemberId();

    activitystatus = "Active";

    members.push_back(member(name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid));
}

void memberTerminal()
{
    int userinput, userinput2;
    string memberid;
    do
    {
        cout << "Enter 1 if you are an existing member or enter 2 if you are a new member: ";
        cin >> userinput;
        if ((userinput != 1) && (userinput != 2))
        {
            cout << "Enter 1 or 2 only!" << endl;
        }
    } while ((userinput != 1) && (userinput != 2));

    if (userinput == 2)
    {
        newRegistration();
    }
    else
    {
        do
        {
            cout << "Press 1 to check in or press 2 to check out: ";
            cin >> userinput2;
            if ((userinput2 != 1) && (userinput2 != 2))
            {
                cout << "Enter 1 or 2 only!" << endl;
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

void updateMemberInformation(string memberid)
{
    int actioninput2;

    do
    {
        cout << "Press 1 to edit Membership type of User; Press 2 to edit Membership duration of user; Press 3 to edit activity status of user; Press 4 to edit contact details of user";
        cin >> actioninput2;
        if ((actioninput2 != 1) && (actioninput2 != 2) && (actioninput2 != 3) && (actioninput2 != 4))
        {
            cout << "Enter a number ranging from 1-4 only!" << endl;
        }
    } while ((actioninput2 != 1) && (actioninput2 != 2) && (actioninput2 != 3) && (actioninput2 != 4));

    string name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus;

    int lastindex = members.size() - 1;
    int updateindex;
    int index = 0;
    bool recordfound = false;
    while ((!recordfound) && (index <= lastindex))
    {
        if (members[index].getMemberId() == memberid)
        {
            recordfound = true;
            updateindex = index;
        }
        ++index;
    }

    if (recordfound)
    {
        if (actioninput2 == 1)
        {
            cout << "The list of membership types and their corresponding monthly fee is mentioned below: " << endl;
            cout << "   1. Silver - Gym only (monthly: $10, yearly: $110)" << endl;
            cout << "   2. Silver+ - Gym and Cardio only (monthly: $15.5, yearly: $160)" << endl;
            cout << "   3. Gold - Gym only with a trainer (monthly: $30, yearly: $300)" << endl;
            cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl << endl;

            int userinput;
            do
            {
                if ((userinput != 1) && (userinput != 2) && (userinput != 3) && (userinput != 4))
                {
                    cout << "Enter number ranging from 1-4 only";
                }
                cout << "Enter the number of membership you want (For Silver, press 1; For Silver+, press 2; For Gold; press 3; For Platinum, press 4)" << endl;
                cin >> userinput;
            } while ((userinput != 1) && (userinput != 2) && (userinput != 3) && (userinput != 4));

            if (userinput == 1) {
                membershiptype = "Silver";
            }
            else if (userinput == 2) {
                membershiptype = "Silver+";
            }
            else if (userinput == 3) {
                membershiptype = "Gold";
            }
            else {
                membershiptype = "Platinum";
            }

            members[updateindex].setMembershipType(membershiptype);

        }
        else if (actioninput2 == 2)
        {
            cout << "The list of membership types and their corresponding monthly fee is mentioned below: " << endl;
            cout << "   1. Silver - Gym only (monthly: $10, yearly: $110)" << endl;
            cout << "   2. Silver+ - Gym and Cardio only (monthly: $15.5, yearly: $160)" << endl;
            cout << "   3. Gold - Gym only with a trainer (monthly: $30, yearly: $300)" << endl;
            cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl << endl;

            int userinput;
            do
            {
                if ((userinput != 1) && (userinput != 2))
                {
                    cout << "Enter 1 or 2 only!" << endl;
                }
                cout << "Enter 1 if you want monthly membership or enter 2 if you want yearly membership: " << endl;
                cin >> userinput;
            } while ((userinput != 1) && (userinput != 2));
            
            if (userinput == 1) {
                membershipduration = "Monthly";
            }
            else {
                membershipduration = "Yearly";
            }

            members[updateindex].setMembershipDuration(membershipduration);
        }
        else if (actioninput2 == 3)
        {
            int userinput;
            do
            {
                if ((userinput != 1) && (userinput != 0))
                {
                    cout << "Enter 1 or 0 only!" << endl;
                }
                cout << "Enter 1 to set activity status of user as active or 0 to set activity status of user as inactive" << endl;
                cin >> userinput;
            } while ((userinput != 1) && (userinput != 0));
            
            if (userinput == 0) {
                activitystatus = "Inactive";
            }
            else {
                activitystatus = "Active";
            }

            members[updateindex].setActivityStatus(activitystatus);
        }
        else
        {
            string newnumber;
            cout << "Enter new contact number of user: ";
            cin >> newnumber;
            contactno = newnumber;

            members[updateindex].setContactNo(contactno);
        }
    }
    else
    {
        cout << "Record not found!";
    }
}

void searchMember(string memberid)
{
    string name, contactno, membershipstartdate, membershipduration, membershiptype, activitystatus;

    bool recordfound = false;
    int lastindex = members.size() - 1;
    int index = 0;

    do
    {
        if (members[index].getMemberId() == memberid)
        {
            name = members[index].getName();
            contactno = members[index].getContactNo();
            membershipstartdate = members[index].getMembershipStartDate();
            membershipduration = members[index].getMembershipDuration();
            membershiptype = members[index].getMembershipType();
            activitystatus = members[index].getActivityStatus();
            recordfound = true;
        }

        if ((index == lastindex) && (!recordfound))
        {
            cout << "Error: Invalid Member ID." << endl;
            cout << "Redirecting back to Manager Terminal" << endl;
        }
        ++index;
    } while (!recordfound && (index <= lastindex));

    cout << "Name: " << name << endl;
    cout << "Contact Number: " << contactno << endl;
    cout << "Membership Start Date: " << membershipstartdate << endl;
    cout << "Membership Type: " << membershiptype << endl;
    cout << "Membership Duration: " << membershipduration << endl;
    cout << "Activity Status: " << activitystatus << endl;
}

void managerTerminal()
{
    int actioninput;
    cout << "Select any action you want from the list below: " << endl;
    cout << "   1, Update Member Information" << endl;
    cout << "   2, Search Member Details" << endl;
    cout << "   3, Report Generation" << endl;

    do
    {
        cout << "Enter 1 to Update Member Information; Enter 2 to Search for Member Details; Enter 3 to Generate Report: "; // Report Generation to be done later
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
    else if (actioninput == 1)
    {
        string memberid;

        cout << "Enter the member ID of member you want to edit the information for: ";
        cin >> memberid;

        bool recordfound;
        int index = 0;
        int lastindex = members.size() - 1;
        do {
            if (members[index].getMemberId() == memberid)
            {
                recordfound = true;
            }
        } while ((index <= lastindex) && !recordfound);
        if (recordfound)
        {
            updateMemberInformation(memberid);
        }
        else
        {
            cout << "Error: Record not found!";
        }
    }
}

bool passwordCheck()
{
    int attempts = 1;
    string password;
    string correctpassword = "FitnessGym123";
    bool access = false;

    cout << "Enter password to access Manager terminal. You only have four tries to enter correct password." << endl;

    do
    {
        cout << "Password: ";
        cin >> password;
        if (password == correctpassword)
        {
            access = true;
            cout << "Access Granted!" << endl;
        }
        else
        {
            cout << "Wrong password. Please Try again!" << endl;
        }
    } while (attempts <= 4 && !access);

    if (!access)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    readMainFile();
    readAttendanceFile();
    int userinput, userinput2;
    cout << "Welcome to Gym Management System!" << endl;
    do
    {
        cout << "Enter 1 if you are a Member or enter 2 if you are a Manager: ";
        cin >> userinput;
        if ((userinput != 1) && (userinput != 2))
        {
            cout << "Enter 1 or 2 only!" << endl;
        }
    } while ((userinput != 1) && (userinput != 2));

    if (userinput == 1)
    {
        memberTerminal();
    }
    else
    {
        if (passwordCheck())
        {
            managerTerminal();
        }
        else
        {
            cout << "Access Denied!" << endl
                 << "Restarting System......";
            main();
        }
    }

    writeMainFile();
    writeAttendanceFile();

    return 0;
}