#pragma once
#include "../LinkList/LinkedList.cpp"
#include <iostream>

using namespace std;

struct Queue {
    LinkedList list;

    void enqueue(void* data) {
        list.append(data);
    }

    void* dequeue() {
        if (isEmpty()) return nullptr;
        ListNode* front = list.head;
        void* data = front->data;
        list.remove(front);
        return data;
    }

    ListNode* getFront() {
        return list.head;
    }

    bool isEmpty() {
        return list.count == 0;
    }
    
    int size() {
        return list.count;
    }
    
    void clear() {
        list.clear();
    }
};
