#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "../LinkList/LinkedList.cpp"

// ====================== HASH ENTRY ======================

struct HashEntry {
    string key;
    void* value;
    HashEntry(string k, void* v) {
        key = k;
        value = v;
    }
};

// ====================== HASH TABLE ======================

class HashTable {
private:
    static const int SIZE = 101;
    LinkedList table[SIZE];

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % SIZE;
        }
        return hash;
    }

public:
    void insert(const string& key, void* value) {
        int index = hashFunction(key);
        HashEntry* entry = new HashEntry(key, value);
        table[index].append(entry);
    }

    // Populates a provided array with results and sets count
    void search(const string& key, void** results, int& count, int max_results) {
        count = 0;
        int index = hashFunction(key);
        ListNode* current = table[index].head;
        while (current != nullptr && count < max_results) {
            HashEntry* entry = (HashEntry*)current->data;
            if (entry->key == key) {
                results[count] = entry->value;
                count++;
            }
            current = current->next;
        }
    }

    void clear() {
        for (int i = 0; i < SIZE; i++) {
            ListNode* current = table[i].head;
            while (current != nullptr) {
                HashEntry* entry = (HashEntry*)current->data;
                delete entry;
                current = current->next;
            }
            table[i].clear();
        }
    }

    ~HashTable() {
        clear();
    }
};

