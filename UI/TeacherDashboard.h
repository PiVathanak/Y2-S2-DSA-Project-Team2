#pragma once
#include <string>
#include "../LinkList/LinkedList.h"

using namespace std;

class TeacherDashboard {
public:
    static void render(string userId, LinkedList& teacherList, LinkedList& enrollList, LinkedList& studentList);
};
