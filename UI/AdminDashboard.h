#pragma once
#include "../LinkList/LinkedList.h"
#include "../Queue/Queue.h"

class AdminDashboard {
public:
    static void render(LinkedList& studentList, Queue& pendingQueue, LinkedList& enrollList,
                        LinkedList& courseList, LinkedList& teacherList);
};
