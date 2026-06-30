#pragma once
#include "../LinkList/LinkedList.cpp"
#include <iostream>

using namespace std;

struct Stack {
    LinkedList list;

    void push(void* data) {
        // We push onto the tail for O(1) append
        list.append(data);
    }

    void* pop() {
        if (isEmpty()) return nullptr;
        ListNode* topNode = list.tail;
        void* data = topNode->data;
        list.remove(topNode);
        return data;
    }

    void* peek() {
        if (isEmpty()) return nullptr;
        return list.tail->data;
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
