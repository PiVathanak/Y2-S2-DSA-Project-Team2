#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "RegisterUI.h"
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.h"
#include "../tools/CSVManager.h"

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

void RegisterUI::render(LinkedList& studentList) {
    cout << "\n--- Student Registration ---" << endl;
    string name, username, email, password;
    
    cout << "Full Name: ";
    cin >> ws;
    getline(cin, name);
    
    while (true) {
        cout << "Username: ";
        cin >> username;
        if (isUsernameExists(studentList, username)) {
            cout << "Username already exists. Please choose another one." << endl;
        } else {
            break;
        }
    }
    
    cout << "Email: ";
    cin >> email;
    
    cout << "Password: ";
    password = getPasswordReg();
    
    string newId = generateNextStudentId(studentList);
    registerStudent(studentList, newId, name, username, email, password);
    
    cout << "Registration successful! Your ID is " << newId << endl;
    cout << "You can now Login to the Account" << endl;
}
