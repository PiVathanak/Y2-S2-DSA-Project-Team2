#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "BST.h"
#include "../tools/Animation.h"

using namespace std;
// constructor
BST::BST() {
    root = nullptr;
}
// recursive helper function to insert student into BST
BSTNode* BST::insertRec(BSTNode* node, Student* data) {
    if (node == nullptr) {
        return new BSTNode{data, nullptr, nullptr};
    }
    // ASCII comparison i.e. A < B (A left B right)
    if (data->name < node->data->name) {
        node->left = insertRec(node->left, data);
    } else {
        node->right = insertRec(node->right, data);
    }
    return node;
}

// insert student into BST
void BST::insert(Student* data) {
    root = insertRec(root, data);
}
// recursive helper function to collect student in order
void BST::collectInOrderRec(BSTNode* node, Student** arr, int& idx) {
    if (node != nullptr) {
        // left
        collectInOrderRec(node->left, arr, idx);
        // root
        arr[idx++] = node->data;
        // right
        collectInOrderRec(node->right, arr, idx);
    }
}
// collect student in order
void BST::collectInOrder(Student** arr, int& count) {
    count = 0;
    collectInOrderRec(root, arr, count);
}
// recursive helper function to destroy BST
void BST::destroyRec(BSTNode* node) {
    if (node) {
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }
}
// destructor
BST::~BST() {
    destroyRec(root);
}

// Teacher roster rendering helper
void teacherViewEnrolledStudents(LinkedList& rosterList) {
    cout << "\n--- Enrolled Students (Sorted A-Z) ---" << endl;
    BST classRoster;
    ListNode* rNode = rosterList.head;
    while (rNode) {
        classRoster.insert((Student*)rNode->data);
        rNode = rNode->next;
    }

    int n = rosterList.count;
    if (n == 0) {
        cout << "No students enrolled." << endl;
    } else {
        Student** arr = new Student*[n];
        int collected = 0;
        classRoster.collectInOrder(arr, collected);

        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
        cout << "| " << left << setw(8) << "ID" << " | " << setw(28) << "Name" << " | " << setw(33) << "Email" << " |" << endl;
        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;

        for (int j = 0; j < collected; j++) {
            Student* s = arr[j];
            cout << "| " << left << setw(8) << s->student_id
                 << " | " << setw(28) << s->name
                 << " | " << setw(33) << s->email << " |" << endl;
        }
        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;

        delete[] arr;
    }
}
