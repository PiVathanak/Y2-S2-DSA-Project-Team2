#pragma once
#include <string>
#include "../tools/Models.cpp"

using namespace std;

struct ListNode {
    void* data;
    ListNode* next;
    ListNode* prev;
};

struct LinkedList {
    ListNode* head;
    ListNode* tail;
    int count;

    LinkedList();
    void append(void* data);
    void remove(ListNode* node);
    void clear();
    ~LinkedList();
};

// CRUD helpers
void* findData(LinkedList& list, const string& id, const string& dataType);
void deleteNode(LinkedList& list, const string& id, const string& dataType);
void updateNode(LinkedList& list, const string& id, const string& dataType, const string& field, const string& newValue);

// Admin / Dashboard Helpers
void adminAddStudent(LinkedList& studentList);
void adminUpdateStudent(LinkedList& studentList);
void adminDeleteStudent(LinkedList& studentList);
void adminViewStudents(LinkedList& studentList);
void adminAddCourse(LinkedList& courseList, LinkedList& teacherList);

// Authentication & Registration Helpers
bool authenticateUser(LinkedList& adminList, LinkedList& studentList, LinkedList& teacherList,
                      const string& username, const string& password, string& outRole, string& outUserId);
bool isUsernameExists(LinkedList& studentList, const string& username);
string generateNextStudentId(LinkedList& studentList);
void registerStudent(LinkedList& studentList, const string& id, const string& name, const string& username, const string& email, const string& password);
void getTeacherRoster(const string& courseId, LinkedList& enrollList, LinkedList& studentList, LinkedList& rosterList);
void displayCoursesTable(Course** arr, int count, string title, LinkedList& teacherList);



