#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "StudentDashboard.h"
#include "../HashTable/HashTable.h"
#include "../Stack/Stack.h"

using namespace std;

void StudentDashboard::render(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList) {
    HashTable courseHash;
    ListNode* current = courseList.head;
    while (current) {
        Course* course = (Course*)current->data;
        courseHash.insert(course->course_id, course);
        courseHash.insert(course->course_name, course);
        current = current->next;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        system("cls");

        cout << "\n--- Student Menu ---" << endl;
        cout << "1. View available courses" << endl;
        cout << "2. View my enrolled courses" << endl;
        cout << "3. Search for a course" << endl;
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

        switch (choice) {
            case 1:
                studentEnrollCourse(userId, courseList, pendingQueue, sessionStack, enrollList, teacherList);
                break;
            case 2:
                studentViewAndUndoEnrollments(userId, courseList, pendingQueue, sessionStack, enrollList, teacherList);
                break;
            case 3:
                studentSearchCourse(courseHash, teacherList);
                break;
            default:
                cout << "Invalid choice! Please choose again." << endl;
                break;
        }

        cout << "\nPress Enter to continue...";
        string temp;
        getline(cin, temp);
    }
}
