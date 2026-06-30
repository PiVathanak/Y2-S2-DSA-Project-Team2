#pragma once


#include <string>
using namespace std;

struct Admin {
    string admin_id;
    string username;
    string password;
};

struct Student {
    string student_id;
    string name;
    string username;
    string email;
    string password;
    string status; // "pending" or "enrolled"
};

struct Teacher {
    string teacher_id;
    string name;
    string course_id;
    string username;
    string password;
};

struct Course {
    string course_id;
    string course_name;
    string teacher_id;
    string credits;
};

struct Enrollment {
    string enrollment_id;
    string student_id;
    string course_id;
};

struct PendingEnrollment {
    string enrollment_id;
    string student_id;
    string course_id;
};
