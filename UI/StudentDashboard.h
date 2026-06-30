#pragma once
#include <string>
#include "../LinkList/LinkedList.h"
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

using namespace std;

class StudentDashboard {
public:
    static void render(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList);
};
