#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

// Include everything in dependency order
// Headers
#include "tools/Models.cpp"
#include "tools/Animation.h"
#include "LinkList/LinkedList.h"
#include "Queue/Queue.h"
#include "Stack/Stack.h"
#include "Tree/BST.h"
#include "HashTable/HashTable.h"
#include "Sorting/Sorting.h"
#include "tools/CSVManager.h"
#include "UI/AdminDashboard.h"
#include "UI/TeacherDashboard.h"
#include "UI/StudentDashboard.h"
#include "UI/LoginUI.h"
#include "UI/RegisterUI.h"

// Implementations
#include "LinkList/LinkedList.cpp"
#include "Queue/Queue.cpp"
#include "Stack/Stack.cpp"
#include "Tree/BST.cpp"
#include "HashTable/HashTable.cpp"
#include "Sorting/Sorting.cpp"
#include "tools/CSVManager.cpp"
#include "UI/LoginUI.cpp"
#include "UI/RegisterUI.cpp"
#include "UI/AdminDashboard.cpp"
#include "UI/TeacherDashboard.cpp"
#include "UI/StudentDashboard.cpp"

using namespace std;

// Global Data Structures
LinkedList adminList;
LinkedList teacherList;
LinkedList studentList;
LinkedList courseList;
LinkedList enrollList;
Queue pendingQueue;
Stack sessionStack; // Only used for student session

void initializeData() {
    CSVManager::loadAdmins(adminList);
    CSVManager::loadTeachers(teacherList);
    CSVManager::loadStudents(studentList);
    CSVManager::loadCourses(courseList);
    CSVManager::loadEnrollments(enrollList);
    CSVManager::loadPendingEnrollments(pendingQueue);
}

int main() {
    Animation::initConsole();
    cout << Animation::BLUE << "Initializing System Data..." << Animation::RESET << endl;
    initializeData();
    cout << Animation::BLUE << "Data loaded." << Animation::RESET << endl;

    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        system("cls");

        cout << "\n" << Animation::BLUE << "==========================" << Animation::RESET << endl;
        cout << Animation::BOLD << Animation::BLUE << "       WELCOME SYSTEM     " << Animation::RESET << endl;
        cout << Animation::BLUE << "==========================" << Animation::RESET << endl;
        cout << Animation::CYAN << "1." << Animation::RESET << " Login" << endl;
        cout << Animation::CYAN << "2." << Animation::RESET << " Register (for new student)" << endl;
        cout << Animation::CYAN << "0." << Animation::RESET << " Exit" << endl;
        cout << Animation::BLUE << "Select: " << Animation::RESET;
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 0) break;

        if (choice == 1) {
            string role, userId;
            if (LoginUI::login(adminList, studentList, teacherList, role, userId)) { // check all 3 role csv
                if (role == "Admin") {
                    AdminDashboard::render(studentList, pendingQueue, enrollList, courseList, teacherList);
                } else if (role == "Teacher") {
                    TeacherDashboard::render(userId, teacherList, enrollList, studentList);
                } else if (role == "Student") {
                    // Start fresh session stack for the student
                    sessionStack.clear();
                    // Load existing pending enrollments for student into sessionStack
                    ListNode* curr = pendingQueue.getFront();
                    while (curr) {
                        PendingEnrollment* pe = (PendingEnrollment*)curr->data;
                        if (pe->student_id == userId) {
                            sessionStack.push(pe);
                        }
                        curr = curr->next;
                    }
                    StudentDashboard::render(userId, courseList, pendingQueue, sessionStack, enrollList, teacherList);
                }
            } else {
                cout << "\nPress Enter to continue...";
                string temp;
                getline(cin, temp);
            }
        } else if (choice == 2) {
            RegisterUI::render(studentList);
        }
    }
    
    cout << "Exiting system. Goodbye!" << endl;
    return 0;
}
