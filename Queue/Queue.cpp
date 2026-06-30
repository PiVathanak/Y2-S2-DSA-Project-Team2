#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Queue.h"
#include "../tools/CSVManager.h"

using namespace std;

void Queue::enqueue(void* data) {
    list.append(data);
}

void* Queue::dequeue() {
    if (isEmpty()) return nullptr;
    ListNode* front = list.head;
    void* data = front->data;
    list.remove(front);
    return data;
}

ListNode* Queue::getFront() {
    return list.head;
}

bool Queue::isEmpty() {
    return list.count == 0;
}

int Queue::size() {
    return list.count;
}

void Queue::clear() {
    list.clear();
}

static void displayPendingEnrollmentsTable(Queue& pendingQueue, LinkedList& studentList, LinkedList& courseList) {
    cout << "=== Pending Enrollments ===" << endl;
    cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
    cout << "| C.ID  | Course Name                    | S.ID | Name                 | Username        | Email                     | Status   |" << endl;
    cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;

    ListNode* temp = pendingQueue.getFront();
    while (temp) {
        PendingEnrollment* pe = (PendingEnrollment*)temp->data;

        Student* s = (Student*)findData(studentList, pe->student_id, "Student");
        Course* c = (Course*)findData(courseList, pe->course_id, "Course");

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
        
        temp = temp->next;
    }
    cout << "+-------+--------------------------------+------+----------------------+-----------------+---------------------------+----------+" << endl;
}

void adminHandlePendingEnrollments(Queue& pendingQueue, LinkedList& studentList, LinkedList& enrollList, LinkedList& courseList) {
    while (true) {
        if (pendingQueue.isEmpty()) {
            cout << "No pending enrollments." << endl;
            break;
        }

        displayPendingEnrollmentsTable(pendingQueue, studentList, courseList);
        cout << "do you want to accept(1) or reject (0) or go back(9)? ";
        int action;
        cin >> action;

        if (action == 1 || action == 0) {
            ListNode* frontNode = pendingQueue.getFront();
            if (!frontNode) break;

            PendingEnrollment* pe = (PendingEnrollment*)frontNode->data;
            string enrollmentId = pe->enrollment_id;
            string studentId = pe->student_id;
            string courseId = pe->course_id;

            if (action == 1) {
                Enrollment* e = new Enrollment{enrollmentId, studentId, courseId};
                enrollList.append(e);
                CSVManager::saveEnrollments(enrollList);

                updateNode(studentList, studentId, "Student", "status", "enrolled");
                CSVManager::saveStudents(studentList);

                pendingQueue.dequeue();
                CSVManager::savePendingEnrollments(pendingQueue);
                cout << "Approved." << endl;
            } else {
                pendingQueue.dequeue();
                CSVManager::savePendingEnrollments(pendingQueue);
                cout << "Rejected." << endl;
            }
        } else if (action == 9) {
            break;
        }
    }
}
