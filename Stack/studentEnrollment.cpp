#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Course
{
    string courseID;
    string courseName;
    string teacherID;
    int credits;
};

void displayCourses()
{

    ifstream file("../DataBase/Courses.csv");

    if (!file)
    {
        cout << "Cannot open Courses.csv" << endl;
        return;
    }

    string line;

    getline(file, line); // skip header

    cout << "\n========== AVAILABLE COURSES ==========\n";

    while (getline(file, line))
    {

        stringstream ss(line);

        Course c;
        string creditStr;

        getline(ss, c.courseID, ',');
        getline(ss, c.courseName, ',');
        getline(ss, c.teacherID, ',');
        getline(ss, creditStr);
        cout << "[" << creditStr << "]" << endl;
        if (creditStr.empty())
        {
            continue;
        }
        c.credits = stoi(creditStr);

        cout << "Course ID : " << c.courseID << endl;
        cout << "Course    : " << c.courseName << endl;
        cout << "Teacher   : " << c.teacherID << endl;
        cout << "Credits   : " << c.credits << endl;
        cout << "-----------------------------------" << endl;
    }

    file.close();
}

bool courseExists(string courseID)
{

    ifstream file("../DataBase/Courses.csv");

    if (!file)
    {
        return false;
    }

    string line;

    getline(file, line);

    while (getline(file, line))
    {

        stringstream ss(line);

        string id;

        getline(ss, id, ',');

        if (id == courseID)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
string generateEnrollmentID(){

    ifstream file("../DataBase/PendingEnrollment.csv");

    string line;
    string lastID = "";

    while(getline(file,line)){

        if(line.empty()){
            continue;
        }

        stringstream ss(line);
        getline(ss,lastID,',');
    }

    file.close();

    if(lastID.empty()){
        return "EN001";
    }

    int num = stoi(lastID.substr(2));
    num++;

    string id = "EN";

    if(num < 10){
        id += "00";
    }
    else if(num < 100){
        id += "0";
    }

    id += to_string(num);

    return id;
}

void saveEnrollmentRequest(
    string enrollmentID,
    string studentID,
    string courseID)
{

    ofstream file(
        "../DataBase/PendingEnrollment.csv",
        ios::app);

    if (!file)
    {
        cout << "Cannot open pendingEnrollments.csv" << endl;
        return;
    }

    file
        << enrollmentID << ","
        << studentID << ","
        << courseID << ","
        << "PENDING"
        << endl;

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

    saveEnrollmentRequest(
        enrollmentID,
        studentID,
        courseID);

    cout << "\nEnrollment Request Submitted" << endl;
    cout << "Status: PENDING" << endl;
}

int main()
{

    string studentID = "S001";

    enrollCourse(studentID);

    return 0;
}