#pragma once
#include <iostream>
#include <string>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../Tree/BST.cpp"

using namespace std;

class TeacherDashboard {
public:
    static void render(string userId, LinkedList& teacherList, LinkedList& enrollList, LinkedList& studentList) {
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

        cout << "\nWelcome, " << myTeacher->name << "!" << endl;

        while (true) {
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

            if (choice == 0) break;

            if (choice == 1 || choice == 2) {
                BST classRoster;
                ListNode* eNode = enrollList.head;
                while (eNode) {
                    Enrollment* e = (Enrollment*)eNode->data;
                    if (e->course_id == myTeacher->course_id) {
                        ListNode* sNode = studentList.head;
                        while(sNode) {
                            Student* s = (Student*)sNode->data;
                            if (s->student_id == e->student_id && s->status == "enrolled") {
                                classRoster.insert(s);
                                break;
                            }
                            sNode = sNode->next;
                        }
                    }
                    eNode = eNode->next;
                }

                if (choice == 1) {
                    cout << "\n--- Enrolled Students (Sorted A-Z) ---" << endl;
                    classRoster.displaySorted();
                } else if (choice == 2) {
                    cout << "\nEnter student name to search: ";
                    string searchName;
                    cin >> ws; getline(cin, searchName);
                    
                    BSTNode* current = classRoster.root;
                    bool found = false;
                    while (current != nullptr) {
                        if (current->data->name == searchName) {
                            cout << "Found: " << current->data->name << " (ID: " << current->data->student_id << ", Email: " << current->data->email << ")" << endl;
                            found = true;
                            break;
                        } else if (searchName < current->data->name) {
                            current = current->left;
                        } else {
                            current = current->right;
                        }
                    }
                    if (!found) {
                        cout << "Student not found in your course." << endl;
                    }
                }
            }
        }
    }
};
