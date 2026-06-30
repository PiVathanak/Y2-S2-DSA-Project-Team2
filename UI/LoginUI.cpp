#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "LoginUI.h"
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.h"

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

bool LoginUI::login(LinkedList& adminList, LinkedList& studentList, LinkedList& teacherList, string& outRole, string& outUserId) {
    cout << "\n=============================" << endl;
    cout << "     SYSTEM LOGIN PANEL      " << endl;
    cout << "=============================" << endl;
    
    string username, password;
    cout << "Username: ";
    cin >> username;
    cin.ignore(10000, '\n');
    cout << "Password: ";
    password = getPassword();

    if (authenticateUser(adminList, studentList, teacherList, username, password, outRole, outUserId)) {
        cout << "Login successful as " << outRole << "." << endl;
        return true;
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}
