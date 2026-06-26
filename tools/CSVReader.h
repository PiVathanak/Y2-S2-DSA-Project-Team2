#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// ====================== DATA STRUCTURES ======================

struct Student
{
    string student_id;
    string name;
    string email;
    string status;
};

struct Teacher
{
    string teacher_id;
    string name;
    string username;
    string password;
};

struct Course
{
    string course_id;
    string course_name;
    string teacher_id;
    int credits;
};

struct Enrollment
{
    string enrollment_id;
    string student_id;
    string course_id;
    string status;
};

struct User
{
    string pending_id;
    string name;
    string username;
    string password;
};

// ====================== CSV READER FUNCTIONS ======================

class CSVReader
{
public:
    static vector<vector<string>> readCSVRows(const string &csvPath);
    static vector<Student> readStudents(const string &csvPath);
    static vector<Teacher> readTeachers(const string &csvPath);
    static vector<Course> readCourses(const string &csvPath);
    static vector<Enrollment> readEnrollments(const string &csvPath);
    static vector<User> readUsers(const string &csvPath);

private:
    static string trim(const string &str);
    static vector<string> parseLine(const string &line);
};

#endif // CSVREADER_H
