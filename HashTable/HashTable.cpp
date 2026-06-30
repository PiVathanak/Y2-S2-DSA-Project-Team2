#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "HashTable.h"
#include "../Sorting/Sorting.h"

using namespace std;

HashEntry::HashEntry(string k, void* v) {
    key = k;
    value = v;
}

void HashTable::insert(const string& key, void* value) {
    int index = hashFunction(key);
    HashEntry* entry = new HashEntry(key, value);
    table[index].append(entry);
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % SIZE;
    }
    return hash;
}

void HashTable::search(const string& key, void** results, int& count, int max_results) {
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

void HashTable::searchPartial(const string& term, void** results, int& count, int max_results) {
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

void HashTable::clear() {
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

HashTable::~HashTable() {
    clear();
}



// Student search helper
void studentSearchCourse(HashTable& courseHash, LinkedList& teacherList) {
    cout << "\nEnter course ID or Name to search: ";
    string term;
    cin >> ws; getline(cin, term);

    void* rawResults[100];
    int count = 0;
    courseHash.searchPartial(term, rawResults, count, 100);

    if (count == 0) {
        cout << "Course not found." << endl;
    } else {
        Course* results[100];
        for (int i = 0; i < count; i++) results[i] = (Course*)rawResults[i];
        Sorting::mergeSortCoursesByName(results, count);
        displayCoursesTable(results, count, "Search Results", teacherList);
    }
}

// Teacher search student helper
void teacherSearchStudent(LinkedList& rosterList) {
    HashTable ht;
    ListNode* currNode = rosterList.head;
    while (currNode) {
        Student* s = (Student*)currNode->data;
        string lowerName = "";
        for (char c : s->name) lowerName += tolower(c);
        
        string prefix = "";
        for (char c : lowerName) {
            prefix += c;
            ht.insert(prefix, s);
        }
        currNode = currNode->next;
    }

    cout << "\nEnter student name to search: ";
    string searchName;
    cin >> ws; getline(cin, searchName);
    
    string lowerSearch = "";
    for (char c : searchName) lowerSearch += tolower(c);
    
    void* results[100];
    int count = 0;
    ht.search(lowerSearch, results, count, 100);
    
    if (count > 0) {
        cout << "\n--- Search Results ---" << endl;
        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
        cout << "| " << left << setw(8) << "ID" << " | " << setw(28) << "Name" << " | " << setw(33) << "Email" << " |" << endl;
        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
        
        for (int i = 0; i < count; i++) {
            Student* s = (Student*)results[i];
            cout << "| " << left << setw(8) << s->student_id 
                 << " | " << setw(28) << s->name 
                 << " | " << setw(33) << s->email << " |" << endl;
        }
        cout << "+" << string(10, '-') << "+" << string(30, '-') << "+" << string(35, '-') << "+" << endl;
    } else {
        cout << "Student not found in your course." << endl;
    }
}
