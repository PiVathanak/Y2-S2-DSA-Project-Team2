#pragma once
#include <iostream>
#include <iomanip>
#include "../tools/Models.cpp"
#include "../LinkList/CRUD.cpp"

using namespace std;

class AdminDashboard {
private:
    // NOTE: alphabetical sorting was dropped here since the Linklist file
    // doesn't expose a sort function. Say the word if you want one added
    // to LinkedList.cpp and I'll wire it back in.
    static void displayStudentsTable(dataList* studentDB) {
        if (studentDB->n == 0) {
            cout << "No students found." << endl;
            return;
        }

        auto printTable = [&](const string& statusFilter, const string& title) {
            cout << "=== " << title << " ===" << endl;
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;
            cout << "| ID   | Name                 | Username        | Email                     | Status   |" << endl;
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;

            bool found = false;
            DataNode* temp = studentDB->head;
            while (temp) {
                if (temp->dataType == "Student") {
                    Student* s = (Student*)temp->data;
                    if (s->status == statusFilter) {
                        cout << "| " << left << setw(4) << s->student_id
                             << " | " << left << setw(20) << (s->name.length() > 20 ? s->name.substr(0,20) : s->name)
                             << " | " << left << setw(15) << (s->username.length() > 15 ? s->username.substr(0,15) : s->username)
                             << " | " << left << setw(25) << (s->email.length() > 25 ? s->email.substr(0,25) : s->email)
                             << " | " << left << setw(8) << (s->status.length() > 8 ? s->status.substr(0,8) : s->status) << " |" << endl;
                        found = true;
                    }
                }
                temp = temp->next;
            }
            if (!found) {
                cout << "| " << left << setw(84) << "No students in this category." << " |" << endl;
            }
            cout << "+------+----------------------+-----------------+---------------------------+----------+" << endl;
        };

        printTable("enrolled", "Enrolled");
        cout << endl;
        printTable("pending", "Pending");
    }

    static void displayPendingEnrollmentsTable(dataList* pendingDB, dataList* studentDB, dataList* courseDB) {
        cout << "=== Pending Enrollments ===" << endl;
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
        cout << "| C.ID  | Course Name                    | S.ID | Name                 | Username        | Email                     | Status   |" << endl;
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;

        DataNode* temp = pendingDB->head;
        while (temp) {
            if (temp->dataType == "PendingEnrollment") {
                PendingEnrollment* pe = (PendingEnrollment*)temp->data;

                Student* s = (Student*)findData(studentDB, pe->student_id, "Student");
                Course* c = (Course*)findData(courseDB, pe->course_id, "Course");

                string studentName     = s ? s->name : "Unknown";
                string studentUsername = s ? s->username : "Unknown";
                string studentEmail    = s ? s->email : "Unknown";
                string studentStatus   = s ? s->status : "Unknown";
                string courseName      = c ? c->course_name : "Unknown";

                cout << "| " << left << setw(5) << pe->course_id
                     << " | " << left << setw(30) << (courseName.length() > 30 ? courseName.substr(0,30) : courseName)
                     << " | " << left << setw(4) << pe->student_id
                     << " | " << left << setw(20) << (studentName.length() > 20 ? studentName.substr(0,20) : studentName)
                     << " | " << left << setw(15) << (studentUsername.length() > 15 ? studentUsername.substr(0,15) : studentUsername)
                     << " | " << left << setw(25) << (studentEmail.length() > 25 ? studentEmail.substr(0,25) : studentEmail)
                     << " | " << left << setw(8) << (studentStatus.length() > 8 ? studentStatus.substr(0,8) : studentStatus) << " |" << endl;
            }
            temp = temp->next;
        }
        cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
    }

    static void displayTeachersTable(dataList* teacherDB) {
        if (teacherDB->n == 0) {
            cout << "No teachers found." << endl;
            return;
        }

        cout << "=== Teachers ===" << endl;
        cout << "+------+----------------------+-----------+" << endl;
        cout << "| ID   | Name                 | Course ID |" << endl;
        cout << "+------+----------------------+-----------+" << endl;

        DataNode* temp = teacherDB->head;
        while (temp) {
            if (temp->dataType == "Teacher") {
                Teacher* t = (Teacher*)temp->data;
                cout << "| " << left << setw(4) << t->teacher_id
                     << " | " << left << setw(20) << (t->name.length() > 20 ? t->name.substr(0,20) : t->name)
                     << " | " << left << setw(9) << t->course_id << " |" << endl;
            }
            temp = temp->next;
        }
        cout << "+------+----------------------+-----------+" << endl;
    }

public:
    // studentDB / courseDB / enrollDB / pendingDB / teacherDB are each a
    // dedicated dataList holding exactly one dataType.
    static void render(dataList* studentDB, dataList* pendingDB, dataList* enrollDB,
                        dataList* courseDB, dataList* teacherDB) {
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

            // Add student
            if (choice == 1) {
                displayStudentsTable(studentDB);
                string name, username, email, password;
                cout << "Name: "; cin >> ws; getline(cin, name);
                cout << "Username: "; cin >> username;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> password;

                // SXXX
                int newIdNum = studentDB->n + 1;
                string newId = "S";
                if (newIdNum < 10) newId += "00";
                else if (newIdNum < 100) newId += "0";
                newId += to_string(newIdNum);

                Student* s = new Student{newId, name, username, email, password, "pending"};
                addDataNode(studentDB, s, "Student");
                writeDataListToFiles(studentDB);
                cout << "Student added with ID " << newId << "." << endl;
            }
            // Update student
            else if (choice == 2) {
                displayStudentsTable(studentDB);
                string idToUpdate;
                cout << "Student ID to update: ";
                cin >> idToUpdate;
                cin.ignore(10000, '\n');

                Student* s = (Student*)findData(studentDB, idToUpdate, "Student");
                if (!s) {
                    cout << "Not found." << endl;
                } else {
                    string input;

                    cout << "New Name (Current: " << s->name << ") [Press Enter to skip]: ";
                    getline(cin, input);
                    if (!input.empty()) updateNode(studentDB, idToUpdate, "Student", "name", input);

                    cout << "New Username (Current: " << s->username << ") [Press Enter to skip]: ";
                    getline(cin, input);
                    if (!input.empty()) updateNode(studentDB, idToUpdate, "Student", "username", input);

                    cout << "New Email (Current: " << s->email << ") [Press Enter to skip]: ";
                    getline(cin, input);
                    if (!input.empty()) updateNode(studentDB, idToUpdate, "Student", "email", input);

                    cout << "New Password (Current: " << s->password << ") [Press Enter to skip]: ";
                    getline(cin, input);
                    if (!input.empty()) updateNode(studentDB, idToUpdate, "Student", "password", input);
                }
            }
            // Delete student
            else if (choice == 3) {
                displayStudentsTable(studentDB);
                string idToDelete;
                cout << "Student ID to delete: ";
                cin >> idToDelete;
                deleteNode(studentDB, idToDelete, "Student");
            }
            // View all students
            else if (choice == 4) {
                displayStudentsTable(studentDB);
            }
            // View pending enrollments
            else if (choice == 5) {
                while (true) {
                    if (pendingDB->n == 0) {
                        cout << "No pending enrollments." << endl;
                        break;
                    }

                    displayPendingEnrollmentsTable(pendingDB, studentDB, courseDB);
                    cout << "do you want to accept(1) or reject (0) or go back(9)? ";
                    int action;
                    cin >> action;

                    if (action == 1 || action == 0) {
                        // Always handle the oldest request first (head of the
                        // list = first one added, since addDataNode appends
                        // to the tail). Grab its fields before deleteNode
                        // frees the underlying PendingEnrollment.
                        PendingEnrollment* pe = (PendingEnrollment*)pendingDB->head->data;
                        string enrollmentId = pe->enrollment_id;
                        string studentId = pe->student_id;
                        string courseId = pe->course_id;

                        if (action == 1) {
                            Enrollment* e = new Enrollment{enrollmentId, studentId, courseId};
                            addDataNode(enrollDB, e, "Enrollment");
                            writeDataListToFiles(enrollDB);

                            updateNode(studentDB, studentId, "Student", "status", "enrolled");
                            deleteNode(pendingDB, enrollmentId, "PendingEnrollment");
                            cout << "Approved." << endl;
                        } else {
                            deleteNode(pendingDB, enrollmentId, "PendingEnrollment");
                            cout << "Rejected." << endl;
                        }
                    } else if (action == 9) {
                        break;
                    }
                }
            }
            // Add course
            else if (choice == 6) {
                displayTeachersTable(teacherDB);

                string teacherId;
                cout << "Teacher ID: ";
                cin >> teacherId;

                Teacher* t = (Teacher*)findData(teacherDB, teacherId, "Teacher");
                if (!t) {
                    cout << "Invalid Teacher ID" << endl;
                } else {
                    string courseName, credits;
                    cout << "Course Name: "; cin >> ws; getline(cin, courseName);
                    cout << "Credits: "; cin >> credits;

                    // CXXX
                    int newIdNum = courseDB->n + 1;
                    string newId = "C";
                    if (newIdNum < 10) newId += "00";
                    else if (newIdNum < 100) newId += "0";
                    newId += to_string(newIdNum);

                    Course* c = new Course{newId, courseName, teacherId, credits};
                    addDataNode(courseDB, c, "Course");
                    writeDataListToFiles(courseDB);
                    cout << "Course added with ID " << newId << "." << endl;
                }
            }
        }
    }
};