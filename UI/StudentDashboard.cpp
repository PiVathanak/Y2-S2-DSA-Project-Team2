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
#include <cctype>

using namespace std;

class StudentDashboard {
private:
    static string toLower(const string& s) {
        string res = s;
        for (size_t i = 0; i < res.length(); ++i) {
            res[i] = tolower(res[i]);
        }
        return res;
    }

    static void displayCoursesTable(Course** arr, int count, string title, LinkedList& teacherList) {
        cout << "=== " << title << " ===" << endl;
        cout << "+-------+--------------------------------+----------------------+---------+" << endl;
        cout << "| C.ID  | Course Name                    | Teacher Name         | Credits |" << endl;
        cout << "+-------+--------------------------------+----------------------+---------+" << endl;
        if (count == 0) {
            cout << "| " << left << setw(70) << "No courses found." << " |" << endl;
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
            
            cout << "| " << left << setw(5) << c->course_id
                 << " | " << left << setw(30) << (c->course_name.length() > 30 ? c->course_name.substr(0,30) : c->course_name)
                 << " | " << left << setw(20) << (teacherName.length() > 20 ? teacherName.substr(0,20) : teacherName)
                 << " | " << left << setw(7) << c->credits << " |" << endl;
        }
        cout << "+-------+--------------------------------+----------------------+---------+" << endl;
    }

public:
    static void render(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList) {
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
                    cout << "\nEnter Course ID to enroll (or '0' to back): ";
                    string cid;
                    cin >> cid;
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
                        cout << "Invalid Course ID! Please try again." << endl;
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
                }
            } else if (choice == 2) {
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
                
                string lowerTerm = toLower(term);
                Course* results[100];
                int count = 0;
                ListNode* curr = courseList.head;
                while (curr && count < 100) {
                    Course* c = (Course*)curr->data;
                    if (toLower(c->course_name).find(lowerTerm) != string::npos || toLower(c->course_id).find(lowerTerm) != string::npos) {
                        results[count++] = c;
                    }
                    curr = curr->next;
                }
                
                if (count == 0) {
                    cout << "Course not found." << endl;
                } else {
                    Sorting::mergeSortCoursesByName(results, count);
                    displayCoursesTable(results, count, "Search Results", teacherList);
                }
            }
        }
    }
};
