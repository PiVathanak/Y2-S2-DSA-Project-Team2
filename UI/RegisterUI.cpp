#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../tools/CSVManager.cpp"

using namespace std;

// Reads password character-by-character, displaying '*' instead of actual chars
static string getPasswordReg() {
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

class RegisterUI {
public:
    static void render(LinkedList& studentList) {
        cout << "\n--- Student Registration ---" << endl;
        string name, username, email, password;
        
        cout << "Full Name: ";
        cin >> ws;
        getline(cin, name);
        
        cout << "Username: ";
        cin >> username;
        
        // Check if username already exists
        ListNode* curr = studentList.head;
        while (curr) {
            Student* s = (Student*)curr->data;
            if (s->username == username) {
                cout << "Error: Username already exists. Registration failed." << endl;
                return;
            }
            curr = curr->next;
        }
        
        cout << "Email: ";
        cin >> email;
        
        cout << "Password: ";
        password = getPasswordReg();
        
        // Generate new ID: find the highest existing numeric ID to avoid reuse
        int maxIdNum = 0;
        ListNode* idNode = studentList.head;
        while (idNode) {
            Student* existing = (Student*)idNode->data;
            if (existing->student_id.length() > 1) {
                int num = 0;
                string numStr = existing->student_id.substr(1);
                for (int i = 0; i < (int)numStr.length(); i++) {
                    if (numStr[i] >= '0' && numStr[i] <= '9')
                        num = num * 10 + (numStr[i] - '0');
                }
                if (num > maxIdNum) maxIdNum = num;
            }
            idNode = idNode->next;
        }
        int newIdNum = maxIdNum + 1;
        string newId = "S";
        if (newIdNum < 10) newId += "00";
        else if (newIdNum < 100) newId += "0";
        newId += to_string(newIdNum);
        
        Student* s = new Student{newId, name, username, email, password, "pending"};
        studentList.append(s);
        
        CSVManager::saveStudents(studentList);
        
        cout << "Registration successful! Your ID is " << newId << endl;
        cout << "You can now Login to the Account" << endl;
    }
};
