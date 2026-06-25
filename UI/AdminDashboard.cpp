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
                             << " | " << left << setw(20) << (arr[k]->name.length() > 20 ? arr[k]->name.substr(0,20) : arr[k]->name)
                             << " | " << left << setw(15) << (arr[k]->username.length() > 15 ? arr[k]->username.substr(0,15) : arr[k]->username)
                             << " | " << left << setw(25) << (arr[k]->email.length() > 25 ? arr[k]->email.substr(0,25) : arr[k]->email)
                             << " | " << left << setw(8) << (arr[k]->status.length() > 8 ? arr[k]->status.substr(0,8) : arr[k]->status) << " |" << endl;
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

    static void displayPendingEnrollmentsTable(Queue& pendingQueue, LinkedList& studentList, LinkedList& courseList) {
        cout << "=== Pending Enrollments ===" << endl;
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
        cout << "| C.ID  | Course Name                    | S.ID | Name                 | Username        | Email                     | Status   |" << endl;
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;

        ListNode* curr = pendingQueue.getFront();
        while(curr) {
            PendingEnrollment* pe = (PendingEnrollment*)curr->data;
            
            // Find Student
            string studentName = "Unknown";
            string studentUsername = "Unknown";
            string studentEmail = "Unknown";
            string studentStatus = "Unknown";
            ListNode* sNode = studentList.head;
            while(sNode) {
                Student* s = (Student*)sNode->data;
                if (s->student_id == pe->student_id) {
                    studentName = s->name;
                    studentUsername = s->username;
                    studentEmail = s->email;
                    studentStatus = s->status;
                    break;
                }
                sNode = sNode->next;
            }

            // Find Course
            string courseName = "Unknown";
            ListNode* cNode = courseList.head;
            while(cNode) {
                Course* c = (Course*)cNode->data;
                if (c->course_id == pe->course_id) {
                    courseName = c->course_name;
                    break;
                }
                cNode = cNode->next;
            }

            cout << "| " << left << setw(5) << pe->course_id
                 << " | " << left << setw(30) << (courseName.length() > 30 ? courseName.substr(0,30) : courseName)
                 << " | " << left << setw(4) << pe->student_id
                 << " | " << left << setw(20) << (studentName.length() > 20 ? studentName.substr(0,20) : studentName)
                 << " | " << left << setw(15) << (studentUsername.length() > 15 ? studentUsername.substr(0,15) : studentUsername)
                 << " | " << left << setw(25) << (studentEmail.length() > 25 ? studentEmail.substr(0,25) : studentEmail)
                 << " | " << left << setw(8) << (studentStatus.length() > 8 ? studentStatus.substr(0,8) : studentStatus) << " |" << endl;
                 
            curr = curr->next;
        }
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
    }

public:
    static void render(LinkedList& studentList, Queue& pendingQueue, LinkedList& enrollList, LinkedList& courseList) {
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
                displayStudentsTable(studentList);
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
                cin.ignore(10000, '\n');
                
                ListNode* curr = studentList.head;
                bool found = false;
                while(curr) {
                    Student* s = (Student*)curr->data;
                    if (s->student_id == idToUpdate) {
                        string input;
                        
                        cout << "New Name (Current: " << s->name << ") [Press Enter to skip]: ";
                        getline(cin, input);
                        if (!input.empty()) s->name = input;
                        
                        cout << "New Username (Current: " << s->username << ") [Press Enter to skip]: ";
                        getline(cin, input);
                        if (!input.empty()) s->username = input;
                        
                        cout << "New Email (Current: " << s->email << ") [Press Enter to skip]: ";
                        getline(cin, input);
                        if (!input.empty()) s->email = input;
                        
                        cout << "New Password (Current: " << s->password << ") [Press Enter to skip]: ";
                        getline(cin, input);
                        if (!input.empty()) s->password = input;
                        
                        CSVManager::saveStudents(studentList);
                        cout << "Updated successfully." << endl;
                        found = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!found) cout << "Not found." << endl;
            }
            // delete student info
            else if (choice == 3) {
                displayStudentsTable(studentList);
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
                    displayPendingEnrollmentsTable(pendingQueue, studentList, courseList);
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
