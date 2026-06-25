#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../Queue/Queue.cpp"
#include "../tools/CSVManager.cpp"

using namespace std;

class AdminDashboard {
private:
    static void displayStudentsTable(LinkedList& studentList) {
        int n = studentList.count;
        if (n == 0) {
            cout << "No students found." << endl;
            return;
        }

        Student** arr = new Student*[n];
        ListNode* curr = studentList.head;
        int i = 0;
        while(curr && i < n) {
            arr[i] = (Student*)curr->data;
            curr = curr->next;
            i++;
        }

        // Bubble sort by name alphabetically
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j]->name > arr[j+1]->name) {
                    Student* temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }

        auto printTable = [&](const string& statusFilter, const string& title) {
            cout << "=== " << title << " ===" << endl;
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;
            cout << "| ID   | Name                 | Username        | Email                     | Status   |" << endl;
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;
            bool found = false;
            for (int k = 0; k < n; k++) {
                if (arr[k]->status == statusFilter || (statusFilter == "pending" && arr[k]->status != "enrolled")) {
                    if (arr[k]->status == statusFilter) {
                        cout << "| " << left << setw(4) << arr[k]->student_id 
                             << " | " << left << setw(20) << arr[k]->name 
                             << " | " << left << setw(15) << arr[k]->username 
                             << " | " << left << setw(25) << arr[k]->email 
                             << " | " << left << setw(8) << arr[k]->status << " |" << endl;
                        found = true;
                    }
                }
            }
            if (!found) {
                cout << "| " << left << setw(84) << "No students in this category." << " |" << endl;
            }
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;
        };

        printTable("enrolled", "Enrolled");
        cout << endl;
        printTable("pending", "Pending");

        delete[] arr;
    }

public:
    static void render(LinkedList& studentList, Queue& pendingQueue, LinkedList& enrollList) {
        while (true) {
            cout << "\n--- Admin Menu ---" << endl;
            cout << "1. Add student" << endl;
            cout << "2. Update student" << endl;
            cout << "3. Delete student" << endl;
            cout << "4. View all students" << endl;
            cout << "5. View pending enrollments" << endl;
            cout << "0. Logout" << endl;
            cout << "Select: ";
            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (choice == 0) break;
            // Add student info
            if (choice == 1) {
                string name, username, email, password;
                cout << "Name: "; cin >> ws; getline(cin, name);
                cout << "Username: "; cin >> username;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> password;
                // SXXX     
                int newIdNum = studentList.count + 1;
                string newId = "S";
                if (newIdNum < 10) newId += "00";
                else if (newIdNum < 100) newId += "0";
                newId += to_string(newIdNum);
                
                Student* s = new Student{newId, name, username, email, password, "pending"}; 
                studentList.append(s);
                CSVManager::saveStudents(studentList);
                cout << "Student added with ID " << newId << "." << endl;
            }
            // update student info
            else if (choice == 2) {
                displayStudentsTable(studentList);
                string idToUpdate;
                cout << "Student ID to update: ";
                cin >> idToUpdate;
                ListNode* curr = studentList.head;
                bool found = false;
                while(curr) {
                    Student* s = (Student*)curr->data;
                    if (s->student_id == idToUpdate) {
                        cout << "New Name: "; cin >> ws; getline(cin, s->name);
                        CSVManager::saveStudents(studentList);
                        cout << "Updated." << endl;
                        found = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!found) cout << "Not found." << endl;
            }
            // delete student info
            else if (choice == 3) {
                string idToDelete;
                cout << "Student ID to delete: ";
                cin >> idToDelete;
                ListNode* curr = studentList.head;
                while(curr) {
                    Student* s = (Student*)curr->data;
                    if (s->student_id == idToDelete) {
                        studentList.remove(curr);
                        CSVManager::saveStudents(studentList);
                        cout << "Deleted." << endl;
                        break;
                    }
                    curr = curr->next;
                }
            }
            // view all students
            else if (choice == 4) {
                displayStudentsTable(studentList);
            }
            // view pending enrollments
            else if (choice == 5) {
                while (true) {
                    if (pendingQueue.isEmpty()) {
                        cout << "No pending enrollments." << endl;
                        break;
                    }
                    
                    ListNode* curr = pendingQueue.getFront();
                    while(curr) {
                        PendingEnrollment* pe = (PendingEnrollment*)curr->data;
                        cout << "Enrollment ID: " << pe->enrollment_id << " | Student ID: " << pe->student_id << " | Course ID: " << pe->course_id << endl;
                        curr = curr->next;
                    }
                    cout << "do you want to accept(1) or reject (0) or go back(9)? ";
                    int action;
                    cin >> action;
                    
                    if (action == 1) {
                        PendingEnrollment* pe = (PendingEnrollment*)pendingQueue.dequeue();
                        Enrollment* e = new Enrollment{pe->enrollment_id, pe->student_id, pe->course_id};
                        enrollList.append(e);
                        
                        // Update student status to enrolled
                        ListNode* sNode = studentList.head;
                        while(sNode) {
                            Student* s = (Student*)sNode->data;
                            if (s->student_id == pe->student_id) {
                                s->status = "enrolled";
                                break;
                            }
                            sNode = sNode->next;
                        }
                        
                        CSVManager::saveStudents(studentList);
                        CSVManager::saveEnrollments(enrollList);
                        CSVManager::savePendingEnrollments(pendingQueue);
                        delete pe;
                        cout << "Approved." << endl;
                    } else if (action == 0) {
                        PendingEnrollment* pe = (PendingEnrollment*)pendingQueue.dequeue();
                        CSVManager::savePendingEnrollments(pendingQueue);
                        delete pe;
                        cout << "Rejected." << endl;
                    } else if (action == 9) {
                        break;
                    }
                }
            }
        }
    }
};
