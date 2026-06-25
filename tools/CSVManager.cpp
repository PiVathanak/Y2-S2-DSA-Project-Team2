#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../Queue/Queue.cpp"

using namespace std;

class CSVManager {
private:
    static string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        if (start == string::npos) return "";
        return str.substr(start, (end - start + 1));
    }

public:
    static void loadStudents(LinkedList& list) {
        ifstream file("DataBase/Students.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            
            Student* s = new Student();
            int pos = 0;
            int col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) s->student_id = token;
                else if (col == 1) s->name = token;
                else if (col == 2) s->username = token;
                else if (col == 3) s->email = token;
                else if (col == 4) s->password = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 5) s->status = trim(line);
            list.append(s);
        }
        file.close();
    }

    static void saveStudents(LinkedList& list) {
        ofstream file("DataBase/Students.csv");
        file << "student_id,name,username,email,password,status\n";
        ListNode* curr = list.head;
        while (curr) {
            Student* s = (Student*)curr->data;
            file << s->student_id << "," << s->name << "," << s->username << "," 
                 << s->email << "," << s->password << "," << s->status << "\n";
            curr = curr->next;
        }
        file.close();
    }

    static void loadAdmins(LinkedList& list) {
        ifstream file("DataBase/Admin.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            Admin* a = new Admin();
            int pos = 0, col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) a->admin_id = token;
                else if (col == 1) a->username = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 2) a->password = trim(line);
            list.append(a);
        }
        file.close();
    }

    static void loadTeachers(LinkedList& list) {
        ifstream file("DataBase/Teachers.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            Teacher* t = new Teacher();
            int pos = 0, col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) t->teacher_id = token;
                else if (col == 1) t->name = token;
                else if (col == 2) t->course_id = token;
                else if (col == 3) t->username = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 4) t->password = trim(line);
            list.append(t);
        }
        file.close();
    }

    static void loadCourses(LinkedList& list) {
        ifstream file("DataBase/Courses.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            Course* c = new Course();
            int pos = 0, col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) c->course_id = token;
                else if (col == 1) c->course_name = token;
                else if (col == 2) c->teacher_id = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 3) c->credits = trim(line);
            list.append(c);
        }
        file.close();
    }

    static void loadEnrollments(LinkedList& list) {
        ifstream file("DataBase/Enrollments.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            Enrollment* e = new Enrollment();
            int pos = 0, col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) e->enrollment_id = token;
                else if (col == 1) e->student_id = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 2) e->course_id = trim(line);
            list.append(e);
        }
        file.close();
    }

    static void saveEnrollments(LinkedList& list) {
        ofstream file("DataBase/Enrollments.csv");
        file << "enrollment_id,student_id,course_id\n";
        ListNode* curr = list.head;
        while (curr) {
            Enrollment* e = (Enrollment*)curr->data;
            file << e->enrollment_id << "," << e->student_id << "," << e->course_id << "\n";
            curr = curr->next;
        }
        file.close();
    }

    static void loadPendingEnrollments(Queue& q) {
        ifstream file("DataBase/PendingEnrollments.csv");
        if (!file.is_open()) return;
        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (trim(line).empty()) continue;
            PendingEnrollment* p = new PendingEnrollment();
            int pos = 0, col = 0;
            string token;
            while ((pos = line.find(',')) != string::npos) {
                token = trim(line.substr(0, pos));
                if (col == 0) p->enrollment_id = token;
                else if (col == 1) p->student_id = token;
                line.erase(0, pos + 1);
                col++;
            }
            if (col == 2) p->course_id = trim(line);
            q.enqueue(p);
        }
        file.close();
    }

    static void savePendingEnrollments(Queue& q) {
        ofstream file("DataBase/PendingEnrollments.csv");
        file << "enrollment_id,student_id,course_id\n";
        ListNode* curr = q.getFront();
        while (curr) {
            PendingEnrollment* p = (PendingEnrollment*)curr->data;
            file << p->enrollment_id << "," << p->student_id << "," << p->course_id << "\n";
            curr = curr->next;
        }
        file.close();
    }
};
