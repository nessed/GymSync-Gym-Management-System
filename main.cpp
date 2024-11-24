#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>

#define TIME _TIME_
#define DATE _DATE_
using namespace std;

class Member // class definition for the class that is to be used throughout the program. attributes have been saved in private classes for security purposes so values can't be accessed without getters or setters which have been declared as public
{
private:
    string name, contactno, membershiptype, membershipstartdate, membershipduration, activitystatus, memberid;
    vector<string> checktype;
    vector<string> attendancedate;
    vector<string> attendancetime;

public:
    Member(string name, string contactno, string membershipstartdate, string membershiptype, string membershipduration, string activitystatus, string memberid) : name(name), contactno(contactno), membershipstartdate(membershipstartdate), membershiptype(membershiptype), membershipduration(membershipduration), activitystatus(activitystatus), memberid(memberid) {}

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

    string getName() const
    {
        return name;
    }
    string getContactNo() const
    {
        return contactno;
    }
    string getMembershipStartDate() const
    {
        return membershipstartdate;
    }
    string getMembershipType() const
    {
        return membershiptype;
    }
    string getMembershipDuration() const
    {
        return membershipduration;
    }
    string getActivityStatus() const

    {
        return activitystatus;
    }
    string getMemberId() const
    {
        return memberid;
    }
    string getCheckType(int index) const
    {
        return checktype[index];
    }
    string getAttendanceDate(int index) const
    {
        return attendancedate[index];
    }
    string getAttendanceTime(int index) const
    {
        return attendancetime[index];
    }

    int getCheckTypeSize() const // function for determining size of checktype vector
    {
        return checktype.size() - 1;
    }
    int getAttendanceDateSize() const
    {
        return attendancedate.size() - 1;
    }
    int getAttendanceTimeSize() const
    {
        return attendancetime.size() - 1;
    }
};

vector<Member> members; // This vector stores the object of class 'Member' which store the record of a member

void readMainFile() // this function reads the file. it's job is to first store each record as an object and then it pushes the object into the vector
{
    ofstream file3("members.txt", ios::app); // These two lines ensure that the members information file exists
    file3.close();

    ifstream file("members.txt");
    if (file.is_open())
    {
        string name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid;
        while (getline(file, name))
        {
            getline(file, contactno);
            getline(file, membershipstartdate);
            getline(file, membershiptype);
            getline(file, membershipduration);
            getline(file, activitystatus);
            getline(file, memberid);

            members.push_back(Member(name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid)); // Here, a member record is made as an object and pushed into the vector 'members'
        }

        file.close();
    }
    else
    {
        cout << "Error: File containing member details does not exist!" << endl;
        cout << "Exiting Program.......";
    }
}

void writeMainFile() // This function writes the member information to the members information file by extracting member information from members vector which is storing member records
{
    ofstream file("members.txt", ios::trunc);
    if (file.is_open())
    {
        string name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid;
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
        }
        file.close();
    }
    else
    {
        cout << "Error: Cannot write members data to the Main file" << endl;
        cout << "Exiting the Program......";
    }
}

void readAttendanceFile() // This function's job is to read the attendance data from attendance file and store it in the corresponding member object
{
    ofstream file4("attendance.txt", ios::app); // These two lines ensure that the members attendance file exists
    file4.close();

    ifstream file2("attendance.txt");

    if (file2.is_open())
    {
        string checktype, attendancedate, attendancetime, memberid;

        while (getline(file2, checktype))
        {
            getline(file2, attendancedate);
            getline(file2, attendancetime);
            getline(file2, memberid);
            int updateindex = -1;
            int lastindex = members.size() - 1;

            for (int index = 0; index <= lastindex; ++index)
            {
                if (members[index].getMemberId() == memberid)
                {
                    updateindex = index;
                    break;
                }
            }

            if (updateindex != -1)
            {
                members[updateindex].setCheckType(checktype);
                members[updateindex].setAttendanceDate(attendancedate);
                members[updateindex].setAttendanceTime(attendancetime);
            }
        }

        file2.close();
    }
    else
    {
        cout << "Error: Cannot open attendance file!" << endl;
        cout << "Exiting Program......";
    }
}

void writeAttendanceFile() // This function takes members attendance data from objects in 'members' vector and stores it in the file
{
    ofstream file2("attendance.txt", ios::trunc);

    if (file2.is_open())
    {
        int lastindex1 = members.size() - 1; // for vectors

        for (int index = 0; index <= lastindex1; ++index)
        {
            int lastindex2;
            string memberid;

            lastindex2 = members[index].getAttendanceDateSize();

            memberid = members[index].getMemberId();
            for (int index2 = 0; index2 <= lastindex2; ++index2)
            {
                string checktype = "undefined";
                string attendancetime = "undefined";
                string attendancedate = "undefined";

                checktype = members[index].getCheckType(index2);
                attendancedate = members[index].getAttendanceDate(index2);
                attendancetime = members[index].getAttendanceTime(index2);

                if ((checktype != "undefined") && (attendancedate != "undefined") && (attendancetime != "undefined"))
                {
                    file2 << checktype + '\n';
                    file2 << attendancedate + '\n';
                    file2 << attendancetime + '\n';
                    file2 << memberid + '\n';
                }
            }
        }

        file2.close();
    }
    else
    {
        cout << "Cannot open attendance file for writing" << endl;
        cout << "Exiting System......";
    }
}

bool expiryChecker(string registerdate, string membershipduration)
{
    tm registrationtime = {};
    istringstream timeclass(registerdate);
    timeclass >> get_time(&registrationtime, "%b %d %Y"); // Format: "Mon DD YYYY"
    if (timeclass.fail())
    {
        cout << "Error: Invalid registration date format!" << endl;
        return false;
    }

    time_t registrationtime2 = mktime(&registrationtime); // Convert to time_t for seconds calculation
    time_t expirytime;

    // Add 30 or 365 days depending on membership duration
    if (membershipduration == "Monthly")
    {
        expirytime = registrationtime2 + (30 * 24 * 60 * 60);
    }
    else if (membershipduration == "Yearly")
    {
        expirytime = registrationtime2 + (365 * 24 * 60 * 60);
    }
    else
    {
        cout << "Error: Invalid membership duration!" << endl;
        return false;
    }

    time_t currenttime = time(nullptr); // Current date in seconds

    // Return true if membership has expired
    if (difftime(currenttime, expirytime) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getVisitFrequency(int memberindex) // This function returns the total number of times member has visited gym
{
    int size = members[memberindex].getCheckTypeSize();
    int frequency;
    if ((size % 2) == 0)
    {
        frequency = size / 2;
    }
    else
    {
        frequency = (size/2) + 1;
    }
    return frequency;
}

void generateReport() 
{
    int totalrevenue = 0;             
    int totalexpiredmemberships = 0; 

    for (int index = 0; index < members.size(); ++index) 
    {
        Member member = members[index];
        cout << "-----------------------------------" << endl;
        cout << "Report for Member ID: " << member.getMemberId() << endl;
        cout << "Name: " << member.getName() << endl;
        cout << "Membership Type: " << member.getMembershipType() << endl;
        cout << "Membership Duration: " << member.getMembershipDuration() << endl;

        int visitfrequency = getVisitFrequency(index);
        cout << "Visit Frequency: " << visitfrequency << " times" << endl;

        bool isexpired = expiryChecker(member.getMembershipStartDate(), member.getMembershipDuration());
        cout << "Membership Expired: " << (isexpired ? "Yes" : "No") << endl;

        if (isexpired) 
        {
            ++totalexpiredmemberships;
        }

        int membershipfee = 0;
        if (member.getMembershipDuration() == "Yearly") 
        {
            if (member.getMembershipType() == "Silver") 
                membershipfee = 110;
            else if (member.getMembershipType() == "Silver+") 
                membershipfee = 160;
            else if (member.getMembershipType() == "Gold") 
                membershipfee = 300;
            else if (member.getMembershipType() == "Platinum")
                membershipfee = 310;
        } 
        else 
        { 
            if (member.getMembershipType() == "Silver") 
                membershipfee = 10;
            else if (member.getMembershipType() == "Silver+") 
                membershipfee = 16; 
            else if (member.getMembershipType() == "Gold") 
                membershipfee = 30;
            else if (member.getMembershipType() == "Platinum") 
                membershipfee = 32;
        }

        totalrevenue += membershipfee;

        cout << "Membership Fee: $" << membershipfee << endl;
        cout << "-----------------------------------" << endl;
    }

    cout << "===================================" << endl;
    cout << "Total Revenue from All Memberships: $" << totalrevenue << endl;
    cout << "Total Expired Memberships: " << totalexpiredmemberships << endl;
    cout << "===================================" << endl;
}

string calculateDuration(string checkintime, string checkouttime)
{
    int checkinhour = stoi(checkintime.substr(0, 2));
    int checkinminute = stoi(checkintime.substr(3, 2));
    int checkouthour = stoi(checkouttime.substr(0, 2));
    int checkoutminute = stoi(checkouttime.substr(3, 2));

    int durationminutes = (checkouthour * 60 + checkoutminute) - (checkinhour * 60 + checkinminute);
    int hours = durationminutes / 60;
    int minutes = durationminutes % 60;

    return to_string(hours) + " hour(s) and " + to_string(minutes) + " minute(s)";
}

void memberCheckIn(string memberid) // This function stores the check in data of user in the record including date and time of check in
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
    cout<<"You have checked in!"<<endl;
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

    int lastindex = members[updateindex].getCheckTypeSize();

    string checkintime = members[updateindex].getAttendanceTime(lastindex);
    string duration = calculateDuration(checkintime, time);
    cout << "Workout Duration: " << duration << endl;

    members[updateindex].setCheckType("Check-Out");
    members[updateindex].setAttendanceDate(date);
    members[updateindex].setAttendanceTime(time);
    cout<<"You have checked out!"<<endl;

}

string generateMemberId() // This function generates a new unique member id each time
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

void newRegistration() // This function registers a new member by taking information about new members and storing the data of member as an object (record)
{
    string name, contactno, membershipstartdate, membershipduration, membershiptype, activitystatus, memberid;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name); // to ignore spaces between inputs
    cout << "Enter your contact number: ";
    cin >> contactno;
    membershipstartdate = __DATE__;

    cout << "The list of membership types and their corresponding monthly fee is mentioned below: " << endl;
    cout << "   1. Silver - Gym only (monthly: $10, yearly: $110)" << endl;
    cout << "   2. Silver+ - Gym and Cardio only (monthly: $15.5, yearly: $160)" << endl;
    cout << "   3. Gold - Gym only with a trainer (monthly: $30, yearly: $300)" << endl;
    cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl
         << endl;

    int typestatus, durationstatus;

    do
    {
        if ((typestatus != 1) && (typestatus != 2) && (typestatus != 3) && (typestatus != 4))
        {
            cout << "Enter number ranging from 1-4 only ";
        }
        cout << "Enter the number of membership you want (For Silver, Press 1; For Silver+ , Press 2; For Gold; Press 3; For Platinum, Press 4): " << endl;
        cin >> typestatus;
    } while ((typestatus != 1) && (typestatus != 2) && (typestatus != 3) && (typestatus != 4));

    if (typestatus == 1)
    {
        membershiptype = "Silver";
    }
    else if (typestatus == 2)
    {
        membershiptype = "Silver+";
    }
    else if (typestatus == 3)
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
        if ((durationstatus != 1) && (durationstatus != 2))
        {
            cout << "Enter 1 or 2 only!" << endl;
        }
        cout << "Enter 1 if you want monthly membership or enter 2 if you want yearly membership: " << endl;
        cin >> durationstatus;
    } while ((durationstatus != 1) && (durationstatus != 2));

    if (durationstatus == 1)
    {
        membershipduration = "Monthly";
    }
    else
    {
        membershipduration = "Yearly";
    }

    memberid = generateMemberId();

    activitystatus = "Active";

    members.push_back(Member(name, contactno, membershipstartdate, membershiptype, membershipduration, activitystatus, memberid));

    cout << "Registration Successful!" << endl;
    cout << "Your Member ID is " << memberid <<endl;
}

void memberTerminal() // main member menu function, it takes inputs and navigates user to inner menus within the main member function. allows users to register themselves, or check in or check out according to their member status
{
    int memberstatus, checkstatus;
    string memberid;
    do
    {
        cout << "Enter 1 if you are an existing member or enter 2 if you are a new member: ";
        cin >> memberstatus;
        if ((memberstatus != 1) && (memberstatus != 2))
        {
            cout << "Enter 1 or 2 only!" << endl;
        }
    } while ((memberstatus != 1) && (memberstatus != 2));

    if (memberstatus == 2)
    {
        newRegistration();
    }
    else
    {
        do
        {
            cout << "Press 1 to check in or press 2 to check out: ";
            cin >> checkstatus;
            if ((checkstatus != 1) && (checkstatus != 2))
            {
                cout << "Enter 1 or 2 only!" << endl;
            }
        } while ((checkstatus != 1) && (checkstatus != 2));
        bool recordfound = false;

        do
        {
            cout << "Enter your Member ID: ";
            cin >> memberid;

            int lastindex = members.size() - 1;
            int index = 0;
            int updateindex;
            recordfound = false;
            do
            {
                if (members[index].getMemberId() == memberid)
                {
                    recordfound = true;
                    updateindex = index;
                }
                ++index;
            } while ((index <= lastindex) && !recordfound);
            if (recordfound)
            {
                string lastchecktype;
                int lastindex = members[updateindex].getCheckTypeSize();
                if (lastindex > 0)
                {
                    lastchecktype = members[updateindex-1].getCheckType(lastindex);
                    if (checkstatus == 1)
                    {
                        if (lastchecktype != "Check-In")
                        {
                            memberCheckIn(memberid);
                        }
                        else
                        {
                            cout << "Error: You have already checked in before" << endl;
                            cout << "Redirecting to member terminal" << endl;
                            memberTerminal();
                        }
                    }
                    else
                    {
                        if (lastchecktype == "Check-In")
                        {
                            memberCheckIn(memberid);
                        }
                        else
                        {
                            cout << "Error: You have already checked out before" << endl;
                            cout << "Redirecting to member terminal" << endl;
                            memberTerminal();
                        }
                    }
                }
                else
                {
                    if (checkstatus == 1)
                    {
                        memberCheckIn(memberid);
                    }
                    else
                    {
                        memberCheckOut(memberid);
                    }
                }
            }
            else
            {
                cout << "Error: Record Not Found!" << endl;
                cout << "Please Enter correct member ID" << endl;
            }
        } while (!recordfound);
    }
}

void updateMemberInformation(string memberid) // This function asks user about what member information to edit and then edits the preffered information
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
            cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl
                 << endl;

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

            if (userinput == 1)
            {
                membershiptype = "Silver";
            }
            else if (userinput == 2)
            {
                membershiptype = "Silver+";
            }
            else if (userinput == 3)
            {
                membershiptype = "Gold";
            }
            else
            {
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
            cout << "   4. Platinum - Gym, Cardio and a trainer (monnthly: $32, yearly: $310)" << endl
                 << endl;

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

            if (userinput == 1)
            {
                membershipduration = "Monthly";
            }
            else
            {
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

            if (userinput == 0)
            {
                activitystatus = "Inactive";
            }
            else
            {
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

void searchMember(string memberid) // This function is used to loop through the vector storing member record object and find the preffered member object. It then extracts the information from member objects and displays it.
{
    string name, contactno, membershipstartdate, membershipduration, membershiptype, activitystatus;

    bool recordfound = false;
    int lastindex = members.size() - 1;
    int index = 0;
    int updateindex = -1;

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
            updateindex = index;
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
    if (updateindex != -1)
    {
        cout << "Total number of times member visited gym: " << getVisitFrequency(updateindex);
    }
}

void managerTerminal() // main manager interface function, it takes inputs and navigates user to inner menus within the main manager function.
{
    int actioninput;
   
    do
    {
        cout << "Enter 1 to Update Member Information; Enter 2 to Search for Member Details, Enter 3 to Generate Report: "<<endl;
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
        do
        {
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
    else
    {
        generateReport();
    }
}

bool passwordCheck() // This function checks if the password entered by the user is correct to access the manager Terminal.
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
        ++attempts;
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

void expiryStatusNotifier()
{
    for (int index = 0; index < members.size(); ++index)
    {
        // Check if the membership is expired
        bool isexpired = expiryChecker(
            members[index].getMembershipStartDate(),
            members[index].getMembershipDuration());

        if (isexpired)
        {
            cout << "Membership for " << members[index].getName() << " (ID: " << members[index].getMemberId() << ") has expired!" << endl;

            cout << "Do you want to re-register this member? (Enter 1 for Yes, 0 for No): ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                // Call newRegistration() to re-register
                cout << "Redirecting to registration process..." << endl;
                members[index].setActivityStatus("Active");
            }
            else
            {
                members[index].setActivityStatus("Inactive");
                cout << "Membership marked as Inactive." << endl;
            }
        }
    }
}
int main()
{
    // First, we read the data from files to the vector storing the records of members
    readMainFile();
    readAttendanceFile();

    int userinput;
    cout << "Welcome to Gym Management System!" << endl;

    do
    {
        cout << "Enter 1 if you are a Member or enter 2 if you are a Manager: ";
        cin >> userinput;

        if (cin.fail() || (userinput != 1 && userinput != 2)) // Check for invalid input
        {
            cout << "Invalid input! Enter 1 or 2 only!" << endl;
            cin.clear(); // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
        {
            break; // Valid input, exit loop
        }
    } while (true);

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
                 << "Restarting System......" << endl
                 << endl
                 << endl;
            main();
        }
    }

    expiryStatusNotifier();

    // Lastly, data is stored from vector storing members objects to the files, ensuring the files are up to date
    writeAttendanceFile();
    writeMainFile();

    return 0;
}