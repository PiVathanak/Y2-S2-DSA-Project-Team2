#pragma once
#include <iostream>
#include <string>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../tools/CSVManager.cpp"

using namespace std;

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
        cin >> password;
        
        // Generate new SXXX ID
        int newIdNum = studentList.count + 1;
        string newId = "S";
        if (newIdNum < 10) newId += "00";
        else if (newIdNum < 100) newId += "0";
        newId += to_string(newIdNum);
        
        Student* s = new Student{newId, name, username, email, password, "pending"};
        studentList.append(s);
        
        CSVManager::saveStudents(studentList);
        
        cout << "Registration successful! Your ID is " << newId << endl;
        cout << "Please wait for Admin approval." << endl;
    }
};
