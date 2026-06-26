#pragma once

#include <iostream>
#include <string>
#include <cctype>
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

    void searchPartial(const string& term, void** results, int& count, int max_results) {
        count = 0;
        string lowerTerm = term;
        int termLen = lowerTerm.length();
        for (int i = 0; i < termLen; i++) lowerTerm[i] = tolower(lowerTerm[i]);

        for (int i = 0; i < SIZE && count < max_results; i++) {
            ListNode* current = table[i].head;
            while (current != nullptr && count < max_results) {
                HashEntry* entry = (HashEntry*)current->data;
                string lowerKey = entry->key;
                int keyLen = lowerKey.length();
                for (int j = 0; j < keyLen; j++) lowerKey[j] = tolower(lowerKey[j]);

                // Manual substring check: slide a window of width termLen across lowerKey
                bool found = false;
                if (termLen <= keyLen) {
                    for (int j = 0; j <= keyLen - termLen && !found; j++) {
                        bool match = true;
                        for (int k = 0; k < termLen && match; k++) {
                            if (lowerKey[j + k] != lowerTerm[k]) match = false;
                        }
                        if (match) found = true;
                    }
                }

                if (found) {
                    // Skip if this pointer was already added
                    bool dup = false;
                    for (int k = 0; k < count; k++) {
                        if (results[k] == entry->value) { dup = true; break; }
                    }
                    if (!dup) results[count++] = entry->value;
                }
                current = current->next;
            }
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

