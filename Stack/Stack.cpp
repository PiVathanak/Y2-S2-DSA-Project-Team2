#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Stack.h"
#include "../tools/CSVManager.h"
#include "../tools/Animation.h"

using namespace std;

void Stack::push(void* data) {
    list.append(data);
}

void* Stack::pop() {
    if (isEmpty()) return nullptr;
    ListNode* topNode = list.tail;
    void* data = topNode->data;
    list.remove(topNode);
    return data;
}

void* Stack::peek() {
    if (isEmpty()) return nullptr;
    return list.tail->data;
}

bool Stack::isEmpty() {
    return list.count == 0;
}

int Stack::size() {
    return list.count;
}

void Stack::clear() {
    list.clear();
}




void studentEnrollCourse(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList) {
    int count = courseList.count;
    Course** arr = new Course*[count];
    ListNode* curr = courseList.head;
    int i = 0;
    while (curr && i < count) {
        arr[i++] = (Course*)curr->data;
        curr = curr->next;
    }
    displayCoursesTable(arr, count, "All Courses", teacherList);
    delete[] arr;

    while (true) {
        cout << "\nEnter " << Animation::CYAN << "Course ID" << Animation::RESET << " to enroll (or '" << Animation::CYAN << "0" << Animation::RESET << "' to back): ";
        string cid;
        cin >> cid;
        cin.ignore(10000, '\n');
        if (cid == "0") break;

        bool isValidCourse = false;
        ListNode* clNode = courseList.head;
        while (clNode) {
            Course* c = (Course*)clNode->data;
            if (c->course_id == cid) {
                isValidCourse = true;
                break;
            }
            clNode = clNode->next;
        }

        if (!isValidCourse) {
            cout << "\033[1;31mInvalid Course ID! Please try again.\033[0m" << endl;
            continue;
        }

        bool exists = false;
        
        ListNode* eNode = enrollList.head;
        while(eNode) {
            Enrollment* e = (Enrollment*)eNode->data;
            if (e->student_id == userId && e->course_id == cid) {
                exists = true; break;
            }
            eNode = eNode->next;
        }
        
        ListNode* pNode = pendingQueue.getFront();
        while(pNode && !exists) {
            PendingEnrollment* pe = (PendingEnrollment*)pNode->data;
            if (pe->student_id == userId && pe->course_id == cid) {
                exists = true; break;
            }
            pNode = pNode->next;
        }
        
        if (exists) {
            cout << "\033[1;31mYou are already enrolled or pending for this course!\033[0m" << endl;
        } else {
            Animation::showLoading("Enrolling in course " + cid);
            
            int nextId = enrollList.count + pendingQueue.size() + 1;
            string eid = "E";
            if (nextId < 10) eid += "00";
            else if (nextId < 100) eid += "0";
            eid += to_string(nextId);
            
            PendingEnrollment* pe = new PendingEnrollment{eid, userId, cid};
            pendingQueue.enqueue(pe);
            
            sessionStack.push(pe);
            CSVManager::savePendingEnrollments(pendingQueue);
            
            cout << Animation::CYAN << "Successfully added to pending list. Please wait for admin approval." << Animation::RESET << endl;
        }
    }
}

void studentViewAndUndoEnrollments(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList) {
    while (true) {
        cout << "\n--- My Courses ---" << endl;
        
        int enrolledCount = 0;
        Course* enrolledArr[100];
        ListNode* eNode = enrollList.head;
        while(eNode) {
            Enrollment* e = (Enrollment*)eNode->data;
            if (e->student_id == userId) {
                ListNode* cNode = courseList.head;
                while (cNode) {
                    Course* c = (Course*)cNode->data;
                    if (c->course_id == e->course_id) {
                        enrolledArr[enrolledCount++] = c;
                        break;
                    }
                    cNode = cNode->next;
                }
            }
            eNode = eNode->next;
        }
        displayCoursesTable(enrolledArr, enrolledCount, "Enrolled", teacherList);
        cout << endl;
        
        int pendingCount = 0;
        Course* pendingArr[100];
        ListNode* pNode = pendingQueue.getFront();
        while(pNode) {
            PendingEnrollment* pe = (PendingEnrollment*)pNode->data;
            if (pe->student_id == userId) {
                ListNode* cNode = courseList.head;
                while (cNode) {
                    Course* c = (Course*)cNode->data;
                    if (c->course_id == pe->course_id) {
                        pendingArr[pendingCount++] = c;
                        break;
                    }
                    cNode = cNode->next;
                }
            }
            pNode = pNode->next;
        }
        displayCoursesTable(pendingArr, pendingCount, "Pending", teacherList);

        if (pendingCount > 0 && !sessionStack.isEmpty()) {
            cout << "\nDo you want to undo your last pending enrollment? (Y/N): ";
            string ans;
            cin >> ans;
            cin.ignore(10000, '\n');
            if (ans == "Y" || ans == "y") {
                PendingEnrollment* pe = (PendingEnrollment*)sessionStack.peek();
                
                ListNode* curr = pendingQueue.list.head;
                bool removedFromQueue = false;
                while (curr) {
                    if (curr->data == pe) {
                        pendingQueue.list.remove(curr);
                        removedFromQueue = true;
                        break;
                    }
                    curr = curr->next;
                }
                
                if (removedFromQueue) {
                    sessionStack.pop();
                    delete pe;
                    CSVManager::savePendingEnrollments(pendingQueue);
                    cout << "Done! Successful undo." << endl;
                } else {
                    cout << "Error: Could not undo." << endl;
                    sessionStack.pop();
                    break;
                }
            } else {
                break;
            }
        } else {
            break;
        }
    }
}
