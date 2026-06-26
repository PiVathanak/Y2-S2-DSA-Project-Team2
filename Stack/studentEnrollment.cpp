#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../tools/CSVReader.cpp"
using namespace std;

void displayCourses()
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/Courses.csv");

    cout << "\n========== AVAILABLE COURSES ==========" << endl;

    for (const auto &fields : rows)
    {
        if (fields.size() < 4)
        {
            continue;
        }

        cout << "Course ID : " << fields[0] << endl;
        cout << "Course    : " << fields[1] << endl;
        cout << "Teacher   : " << fields[2] << endl;
        cout << "Credits   : " << fields[3] << endl;
        cout << "-----------------------------------" << endl;
    }
}

bool courseExists(string courseID)
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/Courses.csv");

    for (const auto &fields : rows)
    {
        if (!fields.empty() && fields[0] == courseID)
        {
            return true;
        }
    }

    return false;
}

string generateEnrollmentID()
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/PendingEnrollment.csv");

    string lastID = "";

    for (const auto &fields : rows)
    {
        if (fields.empty() || fields[0] == "enrollment_id")
        {
            continue;
        }

        lastID = fields[0];
    }

    if (lastID.empty())
    {
        return "PE001";
    }

    int num = stoi(lastID.substr(2));
    num++;

    string id = "PE";

    if (num < 10)
    {
        id += "00";
    }
    else if (num < 100)
    {
        id += "0";
    }

    id += to_string(num);

    return id;
}

string getActiveStudentID()
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/Students.csv");

    for (const auto &fields : rows)
    {
        if (fields.size() > 6 && fields[6] == "Online")
        {
            return fields[0];
        }
    }

    return "";
}

void saveEnrollmentRequest(string enrollmentID, string studentID, string courseID)
{
    ofstream file("../DataBase/PendingEnrollment.csv", ios::app);

    if (!file)
    {
        cout << "Cannot open PendingEnrollment.csv" << endl;
        return;
    }

    file << enrollmentID << "," << studentID << "," << courseID << endl;
    file.close();
}

void enrollCourse(string studentID)
{
    displayCourses();

    string courseID;
    cout << "\nEnter Course ID: ";
    cin >> courseID;

    if (!courseExists(courseID))
    {
        cout << "Invalid Course ID" << endl;
        return;
    }

    string enrollmentID = generateEnrollmentID();
    saveEnrollmentRequest(enrollmentID, studentID, courseID);

    cout << "\nEnrollment Request Submitted" << endl;
    cout << "Status: PENDING" << endl;
}

int main()
{
    string studentID = getActiveStudentID();

    if (studentID.empty())
    {
        cout << "No active student found" << endl;
        return 0;
    }

    cout << "Current Student: " << studentID << endl;
    enrollCourse(studentID);

    return 0;
}
