#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"

using namespace std;

// Reads password character-by-character, displaying '*' instead of actual chars
static string getPassword() {
    string password = "";
    char ch;
    while ((ch = _getch()) != '\r') {  // '\r' = Enter key
        if (ch == '\b') {              // Backspace
            if (!password.empty()) {
                cout << "\b \b";      // erase the last '*'
                password.pop_back();
            }
        } else if (ch >= 32 && ch < 127) { // printable ASCII only
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

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
        password = getPassword();

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
