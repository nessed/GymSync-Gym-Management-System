oid writeMainFile()
{
    ofstream file("members.txt");
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