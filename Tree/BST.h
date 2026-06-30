#pragma once
#include "../tools/Models.cpp"
#include "../LinkList/LinkedList.h"

struct BSTNode {
    Student* data;
    BSTNode* left;
    BSTNode* right;
};

struct BST {
    BSTNode* root;

    BST();
    BSTNode* insertRec(BSTNode* node, Student* data);
    void insert(Student* data);
    void inOrderRec(BSTNode* node, int& index);
    void displaySorted();
    void collectInOrderRec(BSTNode* node, Student** arr, int& idx);
    void collectInOrder(Student** arr, int& count);
    void destroyRec(BSTNode* node);
    ~BST();
};

// Teacher roster rendering helper
void teacherViewEnrolledStudents(LinkedList& rosterList);
