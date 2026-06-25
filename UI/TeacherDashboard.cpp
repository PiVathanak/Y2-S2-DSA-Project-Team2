#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../HashTable/HashTable.cpp"
#include "../Sorting/Sorting.cpp"


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
                LinkedList rosterList;
                ListNode* eNode = enrollList.head;
                while (eNode) {
                    Enrollment* e = (Enrollment*)eNode->data;
                    if (e->course_id == myTeacher->course_id) {
                        ListNode* sNode = studentList.head;
                        while(sNode) {
                            Student* s = (Student*)sNode->data;
                            if (s->student_id == e->student_id && s->status == "enrolled") {
                                rosterList.append(s);
                                break;
                            }
                            sNode = sNode->next;
                        }
                    }
                    eNode = eNode->next;
                }

                if (choice == 1) {
                    cout << "\n--- Enrolled Students (Sorted A-Z) ---" << endl;
                    int n = rosterList.count;
                    if (n == 0) {
                        cout << "No students enrolled." << endl;
                    } else {
                        Student** arr = new Student*[n];
                        ListNode* curr = rosterList.head;
                        int i = 0;
                        while(curr) {
                            arr[i++] = (Student*)curr->data;
                            curr = curr->next;
                        }
                        
                        Sorting::mergeSortStudentsByName(arr, n);

                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                        cout << "| " << left << setw(8) << "ID" << " | " << setw(28) << "Name" << " | " << setw(33) << "Email" << " |" << endl;
                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                        
                        for (int j = 0; j < n; j++) {
                            Student* s = arr[j];
                            cout << "| " << left << setw(8) << s->student_id 
                                 << " | " << setw(28) << s->name 
                                 << " | " << setw(33) << s->email << " |" << endl;
                        }
                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                        
                        delete[] arr;
                    }
                } else if (choice == 2) {
                    HashTable ht;
                    ListNode* currNode = rosterList.head;
                    while (currNode) {
                        Student* s = (Student*)currNode->data;
                        string lowerName = "";
                        for (char c : s->name) lowerName += tolower(c);
                        
                        string prefix = "";
                        for (char c : lowerName) {
                            prefix += c;
                            ht.insert(prefix, s);
                        }
                        currNode = currNode->next;
                    }

                    cout << "\nEnter student name to search: ";
                    string searchName;
                    cin >> ws; getline(cin, searchName);
                    
                    string lowerSearch = "";
                    for (char c : searchName) lowerSearch += tolower(c);
                    
                    void* results[100];
                    int count = 0;
                    ht.search(lowerSearch, results, count, 100);
                    
                    if (count > 0) {
                        cout << "\n--- Search Results ---" << endl;
                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                        cout << "| " << left << setw(8) << "ID" << " | " << setw(28) << "Name" << " | " << setw(33) << "Email" << " |" << endl;
                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                        
                        for (int i = 0; i < count; i++) {
                            Student* s = (Student*)results[i];
                            cout << "| " << left << setw(8) << s->student_id 
                                 << " | " << setw(28) << s->name 
                                 << " | " << setw(33) << s->email << " |" << endl;
                        }
                        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
                    } else {
                        cout << "Student not found in your course." << endl;
                    }
                }
            }
        }
    }
};
