#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "LoginUI.h"
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.h"
#include "../tools/Animation.h"

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
    cout << "\n" << Animation::BLUE << "=============================" << Animation::RESET << endl;
    cout << Animation::BOLD << Animation::BLUE << "     SYSTEM LOGIN PANEL      " << Animation::RESET << endl;
    cout << Animation::BLUE << "=============================" << Animation::RESET << endl;
    
    string username, password;
    cout << Animation::CYAN << "Username: " << Animation::RESET;
    cin >> username;
    cin.ignore(10000, '\n');
    cout << Animation::CYAN << "Password: " << Animation::RESET;
    password = getPassword();

    Animation::showLoading("Authenticating");

    if (authenticateUser(adminList, studentList, teacherList, username, password, outRole, outUserId)) {
        cout << Animation::CYAN << "Login successful as " << outRole << "." << Animation::RESET << endl;
        return true;
    } else {
        cout << "\033[1;31mInvalid username or password!\033[0m" << endl;
        return false;
    }
}
