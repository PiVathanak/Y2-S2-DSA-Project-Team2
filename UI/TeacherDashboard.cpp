#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "TeacherDashboard.h"
#include "../Tree/BST.h"
#include "../HashTable/HashTable.h"

using namespace std;

void TeacherDashboard::render(string userId, LinkedList& teacherList, LinkedList& enrollList, LinkedList& studentList) {
    Teacher* myTeacher = nullptr;
    ListNode* curr = teacherList.head;
    while(curr) {
        Teacher* t = (Teacher*)curr->data;
        if (t->teacher_id == userId) {
            myTeacher = t;
            break;
        }
        curr = curr->next;
    }

    if (!myTeacher) {
        cout << "Teacher record not found." << endl;
        return;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        system("cls");

        cout << "\nWelcome, " << myTeacher->name << "!" << endl;
        cout << "\n--- Teacher Menu ---" << endl;
        cout << "1. View the students enrolled in my course" << endl;
        cout << "2. Search for a student" << endl;
        cout << "0. Logout" << endl;
        cout << "Select: ";
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 0) break;

        if (choice == 1 || choice == 2) {
            LinkedList rosterList;
            getTeacherRoster(myTeacher->course_id, enrollList, studentList, rosterList);

            switch (choice) {
                case 1:
                    teacherViewEnrolledStudents(rosterList);
                    break;
                case 2:
                    teacherSearchStudent(rosterList);
                    break;
            }
        } else {
            cout << "Invalid choice! Please choose again." << endl;
        }

        cout << "\nPress Enter to continue...";
        string temp;
        getline(cin, temp);
    }
}
