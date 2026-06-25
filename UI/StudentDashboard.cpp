#pragma once
#include <iostream>
#include <string>
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.cpp"
#include "../Queue/Queue.cpp"
#include "../Stack/Stack.cpp"
#include "../HashTable/HashTable.cpp"
#include "../Sorting/Sorting.cpp"
#include "../tools/CSVManager.cpp"

using namespace std;

class StudentDashboard {
public:
    static void render(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList) {
        HashTable courseHash;
        ListNode* cNode = courseList.head;
        while (cNode) {
            Course* c = (Course*)cNode->data;
            courseHash.insert(c->course_id, c);
            courseHash.insert(c->course_name, c);
            cNode = cNode->next;
        }

        while (true) {
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

            if (choice == 0) break;

            if (choice == 1) {
                cout << "\n--- All Courses ---" << endl;
                ListNode* curr = courseList.head;
                while (curr) {
                    Course* c = (Course*)curr->data;
                    cout << c->course_id << " | " << c->course_name << " (Credits: " << c->credits << ")" << endl;
                    curr = curr->next;
                }
                while (true) {
                    cout << "\nEnter Course ID to enroll (or '0' to back): ";
                    string cid;
                    cin >> cid;
                    if (cid == "0") break;

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
                        cout << "You are already enrolled or pending for this course!" << endl;
                    } else {
                        int nextId = enrollList.count + pendingQueue.size() + 1;
                        string eid = "E";
                        if (nextId < 10) eid += "00";
                        else if (nextId < 100) eid += "0";
                        eid += to_string(nextId);
                        
                        PendingEnrollment* pe = new PendingEnrollment{eid, userId, cid};
                        pendingQueue.enqueue(pe);
                        
                        sessionStack.push(pe);
                        CSVManager::savePendingEnrollments(pendingQueue);
                        
                        cout << "successfully added to list Please wait for admin approval" << endl;
                    }

                    cout << "do you want to enroll in another course (Y/n)? ";
                    string ans;
                    cin >> ans;
                    if (ans != "Y" && ans != "y") break;
                }
            } else if (choice == 2) {
                while (true) {
                    cout << "\n--- My Courses ---" << endl;
                    cout << "Approved:" << endl;
                    ListNode* eNode = enrollList.head;
                    while(eNode) {
                        Enrollment* e = (Enrollment*)eNode->data;
                        if (e->student_id == userId) {
                            cout << "- " << e->course_id << endl;
                        }
                        eNode = eNode->next;
                    }
                    
                    cout << "\nPending:" << endl;
                    int pendingCount = 0;
                    ListNode* pNode = pendingQueue.getFront();
                    while(pNode) {
                        PendingEnrollment* pe = (PendingEnrollment*)pNode->data;
                        if (pe->student_id == userId) {
                            cout << "- " << pe->course_id << endl;
                            pendingCount++;
                        }
                        pNode = pNode->next;
                    }

                    if (pendingCount > 0 && !sessionStack.isEmpty()) {
                        cout << "\nDo you want to undo your last pending enrollment? (Y/N): ";
                        string ans;
                        cin >> ans;
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
            } else if (choice == 3) {
                cout << "\nEnter course ID or Name to search: ";
                string term;
                cin >> ws; getline(cin, term);
                
                void* results[100];
                int count = 0;
                courseHash.search(term, results, count, 100);
                
                if (count == 0) {
                    cout << "Value not found" << endl;
                } else {
                    Course** foundCourses = new Course*[count];
                    for (int i = 0; i < count; i++) {
                        foundCourses[i] = (Course*)results[i];
                    }
                    
                    Sorting::mergeSortCoursesByName(foundCourses, count);
                    
                    cout << "\n--- Search Results ---" << endl;
                    for (int i = 0; i < count; i++) {
                        cout << foundCourses[i]->course_id << " | " << foundCourses[i]->course_name << " (Teacher: " << foundCourses[i]->teacher_id << ")" << endl;
                    }
                    
                    delete[] foundCourses;
                }
            }
        }
    }
};
