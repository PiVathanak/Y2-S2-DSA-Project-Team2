#pragma once

#include "../tools/Models.cpp"
#include <iostream>

using namespace std;

struct BSTNode {
    Student* data;
    BSTNode* left;
    BSTNode* right;
};

struct BST {
    BSTNode* root;

    BST() {
        root = nullptr;
    }

    BSTNode* insertRec(BSTNode* node, Student* data) {
        if (node == nullptr) {
            return new BSTNode{data, nullptr, nullptr};
        }
        
        // Sort by student name alphabetically
        if (data->name < node->data->name) {
            node->left = insertRec(node->left, data);
        } else {
            node->right = insertRec(node->right, data);
        }
        return node;
    }

    void insert(Student* data) {
        root = insertRec(root, data);
    }

    void inOrderRec(BSTNode* node, int& index) {
        if (node != nullptr) {
            inOrderRec(node->left, index);
            cout << index++ << ". " << node->data->name << " (ID: " << node->data->student_id << ", Email: " << node->data->email << ")" << endl;
            inOrderRec(node->right, index);
        }
    }

    void displaySorted() {
        int index = 1;
        inOrderRec(root, index);
        if (index == 1) {
            cout << "No students found." << endl;
        }
    }

    // Collect students in sorted (in-order)
    void collectInOrderRec(BSTNode* node, Student** arr, int& idx) {
        if (node != nullptr) {
            collectInOrderRec(node->left, arr, idx);
            arr[idx++] = node->data;
            collectInOrderRec(node->right, arr, idx);
        }
    }

    void collectInOrder(Student** arr, int& count) {
        count = 0;
        collectInOrderRec(root, arr, count);
    }
    
    void destroyRec(BSTNode* node) {
        if (node) {
            destroyRec(node->left);
            destroyRec(node->right);
            delete node;
        }
    }
    
    ~BST() {
        destroyRec(root);
    }
};
