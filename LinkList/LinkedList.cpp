#pragma once
#include <iostream>

using namespace std;

struct ListNode {
    void* data;
    ListNode* next;
    ListNode* prev;
};

struct LinkedList {
    ListNode* head;
    ListNode* tail;
    int count;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    void append(void* data) {
        ListNode* newNode = new ListNode{data, nullptr, tail};
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        count++;
    }

    void remove(ListNode* node) {
        if (!node) return;
        
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        
        delete node;
        count--;
    }

    void clear() {
        ListNode* curr = head;
        while (curr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    
    ~LinkedList() {
        clear();
    }
};
