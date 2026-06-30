#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "../tools/CSVManager.h"
#include "../tools/Animation.h"
#include "../HashTable/HashTable.h"

using namespace std;

// Constructor and core methods
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void LinkedList::append(void* data) {
    ListNode* newNode = new ListNode{data, nullptr, tail};
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    count++;
}

void LinkedList::remove(ListNode* node) {
    if (!node) return;
    
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    
    delete node;
    count--;
}

void LinkedList::clear() {
    ListNode* curr = head;
    while (curr) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {
    clear();
}

// CRUD Helpers
void* findData(LinkedList& list, const string& id, const string& dataType) {
    ListNode* temp = list.head;
    while (temp != nullptr) {
        string currentId = "";
        if (dataType == "Student")
            currentId = ((Student*)temp->data)->student_id;
        else if (dataType == "Teacher")
            currentId = ((Teacher*)temp->data)->teacher_id;
        else if (dataType == "Course")
            currentId = ((Course*)temp->data)->course_id;
        else if (dataType == "Enrollment")
            currentId = ((Enrollment*)temp->data)->enrollment_id;
        else if (dataType == "PendingEnrollment")
            currentId = ((PendingEnrollment*)temp->data)->enrollment_id;
        else if (dataType == "Admin")
            currentId = ((Admin*)temp->data)->admin_id;

        if (currentId == id)
            return temp->data;
        temp = temp->next;
    }
    return nullptr;
}

void deleteNode(LinkedList& list, const string& id, const string& dataType) {
    ListNode* temp = list.head;
    while (temp != nullptr) {
        bool foundId = false;
        if (dataType == "Student")
            foundId = (((Student*)temp->data)->student_id == id);
        else if (dataType == "Teacher")
            foundId = (((Teacher*)temp->data)->teacher_id == id);
        else if (dataType == "Course")
            foundId = (((Course*)temp->data)->course_id == id);
        else if (dataType == "Enrollment")
            foundId = (((Enrollment*)temp->data)->enrollment_id == id);
        else if (dataType == "PendingEnrollment")
            foundId = (((PendingEnrollment*)temp->data)->enrollment_id == id);
        else if (dataType == "Admin")
            foundId = (((Admin*)temp->data)->admin_id == id);

        if (foundId) {
            if (dataType == "Student")
                delete (Student*)temp->data;
            else if (dataType == "Teacher")
                delete (Teacher*)temp->data;
            else if (dataType == "Course")
                delete (Course*)temp->data;
            else if (dataType == "Enrollment")
                delete (Enrollment*)temp->data;
            else if (dataType == "PendingEnrollment")
                delete (PendingEnrollment*)temp->data;
            else if (dataType == "Admin")
                delete (Admin*)temp->data;

            list.remove(temp);
            cout << "Deleted successfully!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Not found!" << endl;
}

void updateNode(LinkedList& list, const string& id, const string& dataType, const string& field, const string& newValue) {
    void* dataPtr = findData(list, id, dataType);
    if (!dataPtr) {
        cout << "Not found!" << endl;
        return;
    }

    if (dataType == "Student") {
        Student* s = (Student*)dataPtr;
        if (field == "name") s->name = newValue;
        else if (field == "username") s->username = newValue;
        else if (field == "email") s->email = newValue;
        else if (field == "password") s->password = newValue;
        else if (field == "status") s->status = newValue;
    } else if (dataType == "Teacher") {
        Teacher* t = (Teacher*)dataPtr;
        if (field == "name") t->name = newValue;
        else if (field == "course_id") t->course_id = newValue;
    } else if (dataType == "Course") {
        Course* c = (Course*)dataPtr;
        if (field == "course_name") c->course_name = newValue;
        else if (field == "teacher_id") c->teacher_id = newValue;
        else if (field == "credits") c->credits = newValue;
    } else if (dataType == "Enrollment") {
        Enrollment* e = (Enrollment*)dataPtr;
        if (field == "student_id") e->student_id = newValue;
        else if (field == "course_id") e->course_id = newValue;
    } else if (dataType == "PendingEnrollment") {
        PendingEnrollment* p = (PendingEnrollment*)dataPtr;
        if (field == "student_id") p->student_id = newValue;
        else if (field == "course_id") p->course_id = newValue;
    } else if (dataType == "Admin") {
        Admin* a = (Admin*)dataPtr;
        if (field == "username") a->username = newValue;
        else if (field == "password") a->password = newValue;
    }
    cout << "Updated successfully!" << endl;
}

// Local helper to display students table inside this file
static void localDisplayStudentsTable(LinkedList& studentList) {
    if (studentList.count == 0) {
        cout << "No students found." << endl;
        return;
    }

    auto printTable = [&](const string& statusFilter, const string& title) {
        int rowCount = 0;
        ListNode* countTemp = studentList.head;
        while (countTemp) {
            Student* s = (Student*)countTemp->data;
            if (s->status == statusFilter) {
                rowCount++;
            }
            countTemp = countTemp->next;
        }

        int charDelay, lineDelay, postLineDelay;
        Animation::getDelaysForCount(rowCount, charDelay, lineDelay, postLineDelay);

        {
            stringstream ss;
            ss << "=== " << title << " ===";
            Animation::printLineDelayed(ss.str(), lineDelay);
        }
        Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);
        Animation::printLineDelayed("| ID   | Name                 | Username        | Email                     | Status   |", lineDelay);
        Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);

        bool found = false;
        ListNode* temp = studentList.head;
        while (temp) {
            Student* s = (Student*)temp->data;
            if (s->status == statusFilter) {
                stringstream ss;
                ss << "| " << left << setw(4) << s->student_id
                     << " | " << left << setw(20) << (s->name.length() > 20 ? s->name.substr(0,20) : s->name)
                     << " | " << left << setw(15) << (s->username.length() > 15 ? s->username.substr(0,15) : s->username)
                     << " | " << left << setw(25) << (s->email.length() > 25 ? s->email.substr(0,25) : s->email)
                     << " | " << left << setw(8) << (s->status.length() > 8 ? s->status.substr(0,8) : s->status) << " |";
                Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            stringstream ss;
            ss << "| " << left << setw(84) << "No students in this category." << " |";
            Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
        }
        Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);
    };

    printTable("enrolled", "Enrolled");
    cout << endl;
    printTable("pending", "Pending");
}

static void localDisplayTeachersTable(LinkedList& teacherList) {
    if (teacherList.count == 0) {
        cout << "No teachers found." << endl;
        return;
    }

    int charDelay, lineDelay, postLineDelay;
    Animation::getDelaysForCount(teacherList.count, charDelay, lineDelay, postLineDelay);

    Animation::printLineDelayed("=== Teachers ===", lineDelay);
    Animation::printLineDelayed("+------+----------------------+-----------+", lineDelay);
    Animation::printLineDelayed("| ID   | Name                 | Course ID |", lineDelay);
    Animation::printLineDelayed("+------+----------------------+-----------+", lineDelay);

    ListNode* temp = teacherList.head;
    while (temp) {
        Teacher* t = (Teacher*)temp->data;
        stringstream ss;
        ss << "| " << left << setw(4) << t->teacher_id
             << " | " << left << setw(20) << (t->name.length() > 20 ? t->name.substr(0,20) : t->name)
             << " | " << left << setw(9) << t->course_id << " |";
        Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
        temp = temp->next;
    }
    Animation::printLineDelayed("+------+----------------------+-----------+", lineDelay);
}

// Admin / Dashboard Helpers
void adminAddStudent(LinkedList& studentList) {
    localDisplayStudentsTable(studentList);
    string name, username, email, password;
    cout << "Name: "; cin >> ws; getline(cin, name);
    cout << "Username: "; cin >> username;
    cout << "Email: "; cin >> email;
    cout << "Password: "; cin >> password;
    cin.ignore(10000, '\n');

    int newIdNum = studentList.count + 1;
    string newId = "S";
    if (newIdNum < 10) newId += "00";
    else if (newIdNum < 100) newId += "0";
    newId += to_string(newIdNum);

    Student* s = new Student{newId, name, username, email, password, "pending"};
    studentList.append(s);
    CSVManager::saveStudents(studentList);
    cout << "Student added with ID " << newId << "." << endl;
    cout << "\nUpdated student list:" << endl;
    localDisplayStudentsTable(studentList);
}

void adminUpdateStudent(LinkedList& studentList) {
    localDisplayStudentsTable(studentList);
    string idToUpdate;
    cout << "Student ID to update: ";
    cin >> idToUpdate;
    cin.ignore(10000, '\n');

    Student* s = (Student*)findData(studentList, idToUpdate, "Student");
    if (!s) {
        cout << "Not found." << endl;
    } else {
        string input;

        cout << "New Name (Current: " << s->name << ") [Press Enter to skip]: ";
        getline(cin, input);
        if (!input.empty()) updateNode(studentList, idToUpdate, "Student", "name", input);

        cout << "New Username (Current: " << s->username << ") [Press Enter to skip]: ";
        getline(cin, input);
        if (!input.empty()) updateNode(studentList, idToUpdate, "Student", "username", input);

        cout << "New Email (Current: " << s->email << ") [Press Enter to skip]: ";
        getline(cin, input);
        if (!input.empty()) updateNode(studentList, idToUpdate, "Student", "email", input);

        cout << "New Password (Current: " << s->password << ") [Press Enter to skip]: ";
        getline(cin, input);
        if (!input.empty()) updateNode(studentList, idToUpdate, "Student", "password", input);

        CSVManager::saveStudents(studentList);
        cout << "\nUpdated student list:" << endl;
        localDisplayStudentsTable(studentList);
    }
}

void adminDeleteStudent(LinkedList& studentList) {
    localDisplayStudentsTable(studentList);
    string idToDelete;
    cout << "Student ID to delete: ";
    cin >> idToDelete;
    cin.ignore(10000, '\n');
    deleteNode(studentList, idToDelete, "Student");
    CSVManager::saveStudents(studentList);
    cout << "\nUpdated student list:" << endl;
    localDisplayStudentsTable(studentList);
}

void adminViewStudents(LinkedList& studentList) {
    localDisplayStudentsTable(studentList);
    
    while (true) {
        cout << "\nSearch for student name [0 to go back]: ";
        string searchName;
        cin >> ws;
        getline(cin, searchName);
        
        if (searchName == "0") {
            break;
        }
        
        HashTable ht;
        ListNode* currNode = studentList.head;
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

        string lowerSearch = "";
        for (char c : searchName) lowerSearch += tolower(c);
        
        void* results[100];
        int count = 0;
        ht.search(lowerSearch, results, count, 100);
        
        if (count > 0) {
            int charDelay, lineDelay, postLineDelay;
            Animation::getDelaysForCount(count, charDelay, lineDelay, postLineDelay);
            
            Animation::printLineDelayed("\n--- Search Results ---", lineDelay);
            Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);
            Animation::printLineDelayed("| ID   | Name                 | Username        | Email                     | Status   |", lineDelay);
            Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);
            
            for (int i = 0; i < count; i++) {
                Student* s = (Student*)results[i];
                stringstream ss;
                ss << "| " << left << setw(4) << s->student_id
                   << " | " << left << setw(20) << (s->name.length() > 20 ? s->name.substr(0,20) : s->name)
                   << " | " << left << setw(15) << (s->username.length() > 15 ? s->username.substr(0,15) : s->username)
                   << " | " << left << setw(25) << (s->email.length() > 25 ? s->email.substr(0,25) : s->email)
                   << " | " << left << setw(8) << (s->status.length() > 8 ? s->status.substr(0,8) : s->status) << " |";
                Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
            }
            Animation::printLineDelayed("+------+----------------------+-----------------+---------------------------+----------+", lineDelay);
        } else {
            cout << "Student not found." << endl;
        }
    }
}

void adminAddCourse(LinkedList& courseList, LinkedList& teacherList) {
    localDisplayTeachersTable(teacherList);

    string teacherId;
    cout << "Teacher ID: ";
    cin >> teacherId;

    Teacher* t = (Teacher*)findData(teacherList, teacherId, "Teacher");
    if (!t) {
        cout << "Invalid Teacher ID" << endl;
    } else {
        string courseName, credits;
        cout << "Course Name: "; cin >> ws; getline(cin, courseName);
        cout << "Credits: "; cin >> credits;
        cin.ignore(10000, '\n');

        int newIdNum = courseList.count + 1;
        string newId = "C";
        if (newIdNum < 10) newId += "00";
        else if (newIdNum < 100) newId += "0";
        newId += to_string(newIdNum);

        Course* c = new Course{newId, courseName, teacherId, credits};
        courseList.append(c);
        CSVManager::saveCourses(courseList);
        cout << "Course added with ID " << newId << "." << endl;
    }
}

bool authenticateUser(LinkedList& adminList, LinkedList& studentList, LinkedList& teacherList,
                      const string& username, const string& password, string& outRole, string& outUserId) {
    // Check Admins
    ListNode* curr = adminList.head;
    while (curr) {
        Admin* a = (Admin*)curr->data;
        if (a->username == username && a->password == password) {
            outRole = "Admin";
            outUserId = a->admin_id;
            return true;
        }
        curr = curr->next;
    }

    // Check Teachers
    curr = teacherList.head;
    while (curr) {
        Teacher* t = (Teacher*)curr->data;
        if (t->username == username && t->password == password) {
            outRole = "Teacher";
            outUserId = t->teacher_id;
            return true;
        }
        curr = curr->next;
    }

    // Check Students
    curr = studentList.head;
    while (curr) {
        Student* s = (Student*)curr->data;
        if (s->username == username && s->password == password) {
            outRole = "Student";
            outUserId = s->student_id;
            return true;
        }
        curr = curr->next;
    }

    return false;
}

bool isUsernameExists(LinkedList& studentList, const string& username) {
    ListNode* curr = studentList.head;
    while (curr) {
        Student* s = (Student*)curr->data;
        if (s->username == username) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

string generateNextStudentId(LinkedList& studentList) {
    int maxIdNum = 0;
    ListNode* idNode = studentList.head;
    while (idNode) {
        Student* existing = (Student*)idNode->data;
        if (existing->student_id.length() > 1) {
            int num = 0;
            string numStr = existing->student_id.substr(1);
            for (int i = 0; i < (int)numStr.length(); i++) {
                if (numStr[i] >= '0' && numStr[i] <= '9')
                    num = num * 10 + (numStr[i] - '0');
            }
            if (num > maxIdNum) maxIdNum = num;
        }
        idNode = idNode->next;
    }
    int newIdNum = maxIdNum + 1;
    string newId = "S";
    if (newIdNum < 10) newId += "00";
    else if (newIdNum < 100) newId += "0";
    newId += to_string(newIdNum);
    return newId;
}

void registerStudent(LinkedList& studentList, const string& id, const string& name, const string& username, const string& email, const string& password) {
    Student* s = new Student{id, name, username, email, password, "pending"};
    studentList.append(s);
    CSVManager::saveStudents(studentList);
}

void getTeacherRoster(const string& courseId, LinkedList& enrollList, LinkedList& studentList, LinkedList& rosterList) {
    ListNode* eNode = enrollList.head;
    while (eNode) {
        Enrollment* e = (Enrollment*)eNode->data;
        if (e->course_id == courseId) {
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
}

void displayCoursesTable(Course** arr, int count, string title, LinkedList& teacherList) {
    int charDelay, lineDelay, postLineDelay;
    Animation::getDelaysForCount(count, charDelay, lineDelay, postLineDelay);

    {
        stringstream ss;
        ss << "=== " << title << " ===";
        Animation::printLineDelayed(ss.str(), lineDelay);
    }
    Animation::printLineDelayed("+-------+--------------------------------+----------------------+---------+", lineDelay);
    Animation::printLineDelayed("| C.ID  | Course Name                    | Teacher Name         | Credits |", lineDelay);
    Animation::printLineDelayed("+-------+--------------------------------+----------------------+---------+", lineDelay);
    if (count == 0) {
        stringstream ss;
        ss << "| " << left << setw(70) << "No courses found." << " |";
        Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
    }
    for (int i = 0; i < count; i++) {
        Course* c = arr[i];
        
        string teacherName = "Unknown";
        ListNode* tNode = teacherList.head;
        while (tNode) {
            Teacher* t = (Teacher*)tNode->data;
            if (t->teacher_id == c->teacher_id) {
                teacherName = t->name;
                break;
            }
            tNode = tNode->next;
        }
        
        stringstream ss;
        ss << "| " << left << setw(5) << c->course_id
             << " | " << left << setw(30) << (c->course_name.length() > 30 ? c->course_name.substr(0,30) : c->course_name)
             << " | " << left << setw(20) << (teacherName.length() > 20 ? teacherName.substr(0,20) : teacherName)
             << " | " << left << setw(7) << c->credits << " |";
        Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
    }
    Animation::printLineDelayed("+-------+--------------------------------+----------------------+---------+", lineDelay);
}



