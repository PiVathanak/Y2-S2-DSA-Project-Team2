#pragma once
#include <string>
#include "../LinkList/LinkedList.h"

using namespace std;

struct HashEntry {
    string key;
    void* value;
    // constructor
    // void* v could be a pointer to a Course or a pointer to a Student
    HashEntry(string k, void* v);
};

class HashTable {
private:
    static const int SIZE = 101;
    LinkedList table[SIZE];

    int hashFunction(const string& key);

public:
    void insert(const string& key, void* value);
    void search(const string& key, void** results, int& count, int max_results);
    void searchPartial(const string& term, void** results, int& count, int max_results);
    void clear();
    ~HashTable();
};

// handle searching Course / students
void studentSearchCourse(HashTable& courseHash, LinkedList& teacherList);
void teacherSearchStudent(LinkedList& rosterList);
