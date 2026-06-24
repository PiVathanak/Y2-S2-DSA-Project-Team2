#include "CSVReader.h"
#include <iostream>

using namespace std;

// ====================== HELPER FUNCTIONS ======================

string CSVReader::trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == string::npos)
        return "";
    return str.substr(start, (end - start + 1));
}

vector<string> CSVReader::parseLine(const string &line)
{
    vector<string> result;
    stringstream ss(line);
    string item;

    while (getline(ss, item, ','))
    {
        result.push_back(trim(item));
    }

    return result;
}

bool CSVReader::isBlankLine(const string &line)
{
    string trimmed = trim(line);
    return trimmed.empty();
}

// ====================== READ STUDENTS ======================

vector<Student> CSVReader::readStudents(const string &csvPath)
{
    vector<Student> students;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return students;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 6)
        {
            Student student;
            student.student_id = fields[0];
            student.name = fields[1];
            student.username = fields[2];
            student.email = fields[3];
            student.password = fields[4];
            student.status = fields[5];
            students.push_back(student);
        }
    }

    file.close();
    return students;
}

// ====================== READ TEACHERS ======================

vector<Teacher> CSVReader::readTeachers(const string &csvPath)
{
    vector<Teacher> teachers;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return teachers;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 3)
        {
            Teacher teacher;
            teacher.teacher_id = fields[0];
            teacher.name = fields[1];
            teacher.course_id = fields[2];
            teachers.push_back(teacher);
        }
    }

    file.close();
    return teachers;
}

// ====================== READ COURSES ======================

vector<Course> CSVReader::readCourses(const string &csvPath)
{
    vector<Course> courses;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return courses;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            Course course;
            course.course_id = fields[0];
            course.course_name = fields[1];
            course.teacher_id = fields[2];
            course.credits = fields[3];
            courses.push_back(course);
        }
    }

    file.close();
    return courses;
}

// ====================== READ ENROLLMENTS ======================

vector<Enrollment> CSVReader::readEnrollments(const string &csvPath)
{
    vector<Enrollment> enrollments;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return enrollments;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 3)
        {
            Enrollment enrollment;
            enrollment.enrollment_id = fields[0];
            enrollment.student_id = fields[1];
            enrollment.course_id = fields[2];
            enrollments.push_back(enrollment);
        }
    }

    file.close();
    return enrollments;
}

// ====================== READ USERS ======================

vector<PendingEnrollment> CSVReader::readPendingEnrollments(const string &csvPath)
{
    vector<PendingEnrollment> pendingEnrollments;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return pendingEnrollments;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 3)
        {
            PendingEnrollment pending;
            pending.enrollment_id = fields[0];
            pending.student_id = fields[1];
            pending.course_id = fields[2];
            pendingEnrollments.push_back(pending);
        }
    }

    file.close();
    return pendingEnrollments;
}

vector<Admin> CSVReader::readAdmins(const string &csvPath)
{
    vector<Admin> admins;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return admins;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 3)
        {
            Admin admin;
            admin.admin_id = fields[0];
            admin.username = fields[1];
            admin.password = fields[2];
            admins.push_back(admin);
        }
    }

    file.close();
    return admins;
}

vector<PendingUser> CSVReader::readPendingUsers(const string &csvPath)
{
    vector<PendingUser> pendingUsers;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return pendingUsers;
    }

    string line;
    bool isHeader = true;

    while (getline(file, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        if (isBlankLine(line))
            continue;

        vector<string> fields = parseLine(line);

        if (fields.size() >= 6)
        {
            PendingUser user;
            user.student_id = fields[0];
            user.name = fields[1];
            user.username = fields[2];
            user.email = fields[3];
            user.password = fields[4];
            user.status = fields[5];
            pendingUsers.push_back(user);
        }
    }

    file.close();
    return pendingUsers;
}
