#pragma once
#include <iostream>
#include "AdminDashboard.h"

using namespace std;

void AdminDashboard::render(LinkedList& studentList, Queue& pendingQueue, LinkedList& enrollList,
                            LinkedList& courseList, LinkedList& teacherList) {
    while (true) {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Update student" << endl;
        cout << "3. Delete student" << endl;
        cout << "4. View all students" << endl;
        cout << "5. View pending enrollments" << endl;
        cout << "6. Add course" << endl;
        cout << "0. Logout" << endl;
        cout << "Select: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1:
                adminAddStudent(studentList);
                break;
            case 2:
                adminUpdateStudent(studentList);
                break;
            case 3:
                adminDeleteStudent(studentList);
                break;
            case 4:
                adminViewStudents(studentList);
                break;
            case 5:
                adminHandlePendingEnrollments(pendingQueue, studentList, enrollList, courseList);
                break;
            case 6:
                adminAddCourse(courseList, teacherList);
                break;
            default:
                cout << "Invalid choice! Please choose again." << endl;
                break;
        }
    }
}