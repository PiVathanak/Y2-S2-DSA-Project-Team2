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

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            Student student;
            student.student_id = fields[0];
            student.name = fields[1];
            student.email = fields[2];
            student.status = fields[3];
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

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            Teacher teacher;
            teacher.teacher_id = fields[0];
            teacher.name = fields[1];
            teacher.username = fields[2];
            teacher.password = fields[3];
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

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            Course course;
            course.course_id = fields[0];
            course.course_name = fields[1];
            course.teacher_id = fields[2];
            course.credits = stoi(fields[3]);
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

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            Enrollment enrollment;
            enrollment.enrollment_id = fields[0];
            enrollment.student_id = fields[1];
            enrollment.course_id = fields[2];
            enrollment.status = fields[3];
            enrollments.push_back(enrollment);
        }
    }

    file.close();
    return enrollments;
}

// ====================== READ USERS ======================

vector<User> CSVReader::readUsers(const string &csvPath)
{
    vector<User> users;
    ifstream file(csvPath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: " << csvPath << endl;
        return users;
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

        vector<string> fields = parseLine(line);

        if (fields.size() >= 4)
        {
            User user;
            user.pending_id = fields[0];
            user.name = fields[1];
            user.username = fields[2];
            user.password = fields[3];
            users.push_back(user);
        }
    }

    file.close();
    return users;
}
