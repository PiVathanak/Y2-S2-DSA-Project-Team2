#pragma once
#include "../LinkList/LinkedList.h"
#include "../Queue/Queue.h"

struct Stack {
    LinkedList list;

    void push(void* data);
    void* pop();
    void* peek();
    bool isEmpty();
    int size();
    void clear();
};

// Student Dashboard handler functions
void studentEnrollCourse(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList);
void studentViewAndUndoEnrollments(string userId, LinkedList& courseList, Queue& pendingQueue, Stack& sessionStack, LinkedList& enrollList, LinkedList& teacherList);
