#pragma once
#include <string>
#include "../LinkList/LinkedList.h"
#include "../Queue/Queue.h"

using namespace std;

class CSVManager {
private:
    static string trim(const string& str);

public:
    static void loadStudents(LinkedList& list);
    static void saveStudents(LinkedList& list);
    static void loadAdmins(LinkedList& list);
    static void loadTeachers(LinkedList& list);
    static void loadCourses(LinkedList& list);
    static void saveCourses(LinkedList& list);
    static void loadEnrollments(LinkedList& list);
    static void saveEnrollments(LinkedList& list);
    static void loadPendingEnrollments(Queue& q);
    static void savePendingEnrollments(Queue& q);
};
