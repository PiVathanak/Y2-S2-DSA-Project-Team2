#pragma once

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
    string username;
    string email;
    string password;
    string status;
};

struct Teacher
{
    string teacher_id;
    string name;
    string course_id;
};

struct Course
{
    string course_id;
    string course_name;
    string teacher_id;
    string credits;
};

struct Enrollment
{
    string enrollment_id;
    string student_id;
    string course_id;
};

struct PendingEnrollment
{
    string enrollment_id;
    string student_id;
    string course_id;
};

struct Admin
{
    string admin_id;
    string username;
    string password;
};

struct PendingUser
{
    string student_id;
    string name;
    string username;
    string email;
    string password;
    string status;
};

// ====================== CSV READER FUNCTIONS ======================

class CSVReader
{
public:
    static vector<Student> readStudents(const string &csvPath);
    static vector<Teacher> readTeachers(const string &csvPath);
    static vector<Course> readCourses(const string &csvPath);
    static vector<Enrollment> readEnrollments(const string &csvPath);
    static vector<PendingEnrollment> readPendingEnrollments(const string &csvPath);
    static vector<Admin> readAdmins(const string &csvPath);
    static vector<PendingUser> readPendingUsers(const string &csvPath);

private:
    static string trim(const string &str);
    static vector<string> parseLine(const string &line);
    static bool isBlankLine(const string &line);
};

