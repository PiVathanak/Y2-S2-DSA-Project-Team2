#pragma once
#include "../LinkList/LinkedList.h"

struct Queue {
    LinkedList list;

    void enqueue(void* data);
    void* dequeue();
    ListNode* getFront();
    bool isEmpty();
    int size();
    void clear();
};

// Admin handler for pending enrollments
void adminHandlePendingEnrollments(Queue& pendingQueue, LinkedList& studentList, LinkedList& enrollList, LinkedList& courseList);
