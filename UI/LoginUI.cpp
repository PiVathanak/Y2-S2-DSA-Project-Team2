#pragma once
#include <iostream>
#include <string>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"

using namespace std;

class LoginUI {
public:
    static bool login(LinkedList& adminList, LinkedList& studentList, LinkedList& teacherList, string& outRole, string& outUserId) {
        cout << "\n=============================" << endl;
        cout << "     SYSTEM LOGIN PANEL      " << endl;
        cout << "=============================" << endl;
        
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        // Check Admins
        ListNode* curr = adminList.head;
        while (curr) {
            Admin* a = (Admin*)curr->data;
            if (a->username == username && a->password == password) {
                outRole = "Admin";
                outUserId = a->admin_id;
                cout << "Login successful as Admin." << endl;
                return true;
            }
            curr = curr->next;
        }

        // Check Teachers
        curr = teacherList.head;
        while (curr) {
            Teacher* t = (Teacher*)curr->data;
            if (t->username == username && t->password == password) {
                outRole = "Teacher";
                outUserId = t->teacher_id;
                cout << "Login successful as Teacher." << endl;
                return true;
            }
            curr = curr->next;
        }

        // Check Students
        curr = studentList.head;
        while (curr) {
            Student* s = (Student*)curr->data;
            if (s->username == username && s->password == password) {
                outRole = "Student";
                outUserId = s->student_id;
                cout << "Login successful as Student." << endl;
                return true;
            }
            curr = curr->next;
        }

        cout << "Invalid credentials." << endl;
        return false;
    }
};
