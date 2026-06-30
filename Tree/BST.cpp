#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "BST.h"
#include "../tools/Animation.h"

using namespace std;

BST::BST() {
    root = nullptr;
}

BSTNode* BST::insertRec(BSTNode* node, Student* data) {
    if (node == nullptr) {
        return new BSTNode{data, nullptr, nullptr};
    }
    
    if (data->name < node->data->name) {
        node->left = insertRec(node->left, data);
    } else {
        node->right = insertRec(node->right, data);
    }
    return node;
}

void BST::insert(Student* data) {
    root = insertRec(root, data);
}

static int localCountNodes(BSTNode* node) {
    if (node == nullptr) return 0;
    return 1 + localCountNodes(node->left) + localCountNodes(node->right);
}

void BST::inOrderRec(BSTNode* node, int& index, int charDelay, int postLineDelay) {
    if (node != nullptr) {
        inOrderRec(node->left, index, charDelay, postLineDelay);
        stringstream ss;
        ss << index << ". " << node->data->name << " (ID: " << node->data->student_id << ", Email: " << node->data->email << ")";
        Animation::typeWriteLine(ss.str(), charDelay, postLineDelay);
        index++;
        inOrderRec(node->right, index, charDelay, postLineDelay);
    }
}

void BST::displaySorted() {
    int index = 1;
    int nodeCount = localCountNodes(root);
    int charDelay, lineDelay, postLineDelay;
    Animation::getDelaysForCount(nodeCount, charDelay, lineDelay, postLineDelay);

    inOrderRec(root, index, charDelay, postLineDelay);
    if (index == 1) {
        Animation::printLineDelayed("No students found.", lineDelay);
    }
}

void BST::collectInOrderRec(BSTNode* node, Student** arr, int& idx) {
    if (node != nullptr) {
        collectInOrderRec(node->left, arr, idx);
        arr[idx++] = node->data;
        collectInOrderRec(node->right, arr, idx);
    }
}

void BST::collectInOrder(Student** arr, int& count) {
    count = 0;
    collectInOrderRec(root, arr, count);
}

void BST::destroyRec(BSTNode* node) {
    if (node) {
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }
}

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
