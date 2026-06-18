#include <iostream>
#include "../tools/CSVReader.h"
using namespace std;
// Generic node to store CSV data
struct DataNode
{
    void *data;
    string dataType;
    DataNode *next;
};

struct dataList
{
    int n;
    DataNode *head;
    DataNode *tail;
};

// ====================== DATA LIST OPERATIONS ======================

dataList *createDataList()
{
    dataList *dl = new dataList();
    dl->n = 0;
    dl->head = nullptr;
    dl->tail = nullptr;
    return dl;
}

void addDataNode(dataList *dl, void *data, string dataType)
{
    DataNode *newNode = new DataNode();
    newNode->data = data;
    newNode->dataType = dataType;
    newNode->next = nullptr;

    if (dl->n == 0)
    {
        dl->head = newNode;
        dl->tail = newNode;
    }
    else
    {
        dl->tail->next = newNode;
        dl->tail = newNode;
    }
    dl->n++;
}

// ====================== UPDATE ======================

void updateNode(dataList *dl, const string &id, const string &dataType, const string &field, const string &newValue)
{
    DataNode *temp = dl->head;

    while (temp != nullptr)
    {
        if (temp->dataType == dataType)
        {
            if (dataType == "Student")
            {
                Student *s = (Student *)temp->data;
                if (s->student_id == id)
                {
                    if (field == "name")
                        s->name = newValue;
                    else if (field == "email")
                        s->email = newValue;
                    else if (field == "status")
                        s->status = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "Teacher")
            {
                Teacher *t = (Teacher *)temp->data;
                if (t->teacher_id == id)
                {
                    if (field == "name")
                        t->name = newValue;
                    else if (field == "username")
                        t->username = newValue;
                    else if (field == "password")
                        t->password = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "Course")
            {
                Course *c = (Course *)temp->data;
                if (c->course_id == id)
                {
                    if (field == "course_name")
                        c->course_name = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "Enrollment")
            {
                Enrollment *e = (Enrollment *)temp->data;
                if (e->enrollment_id == id)
                {
                    if (field == "status")
                        e->status = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "User")
            {
                User *u = (User *)temp->data;
                if (u->pending_id == id)
                {
                    if (field == "name")
                        u->name = newValue;
                    else if (field == "username")
                        u->username = newValue;
                    else if (field == "password")
                        u->password = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
        }
        temp = temp->next;
    }
    cout << "Not found!" << endl;
}

// ====================== DELETE ======================

void deleteNode(dataList *dl, const string &id, const string &dataType)
{
    if (dl->n == 0)
    {
        cout << "Cannot delete" << endl;
        return;
    }

    DataNode *temp = dl->head;
    DataNode *prev = nullptr;

    // Find the node to delete
    while (temp != nullptr)
    {
        if (temp->dataType == dataType)
        {
            bool foundId = false;

            if (dataType == "Student")
            {
                Student *s = (Student *)temp->data;
                foundId = (s->student_id == id);
            }
            else if (dataType == "Teacher")
            {
                Teacher *t = (Teacher *)temp->data;
                foundId = (t->teacher_id == id);
            }
            else if (dataType == "Course")
            {
                Course *c = (Course *)temp->data;
                foundId = (c->course_id == id);
            }
            else if (dataType == "Enrollment")
            {
                Enrollment *e = (Enrollment *)temp->data;
                foundId = (e->enrollment_id == id);
            }
            else if (dataType == "User")
            {
                User *u = (User *)temp->data;
                foundId = (u->pending_id == id);
            }

            if (foundId)
            {
                // Delete found node
                if (prev == nullptr)
                {
                    // Delete head
                    dl->head = temp->next;
                    if (dl->n == 1)
                    {
                        dl->tail = nullptr;
                    }
                }
                else
                {
                    // Delete middle or tail
                    prev->next = temp->next;
                    if (temp == dl->tail)
                    {
                        dl->tail = prev;
                    }
                }
                delete temp->data;
                delete temp;
                dl->n--;
                cout << "Deleted successfully!" << endl;
                return;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Not found!" << endl;
}

// ====================== DISPLAY OPERATIONS ======================

void displayDataList(dataList *dl)
{
    DataNode *temp = dl->head;
    int index = 0;

    while (temp != nullptr)
    {
        if (temp->dataType == "Student")
        {
            Student *s = (Student *)temp->data;
            cout << index++ << ". [Student] ID: " << s->student_id << " | Name: " << s->name
                 << " | Email: " << s->email << " | Status: " << s->status << endl;
        }
        else if (temp->dataType == "Teacher")
        {
            Teacher *t = (Teacher *)temp->data;
            cout << index++ << ". [Teacher] ID: " << t->teacher_id << " | Name: " << t->name
                 << " | Username: " << t->username << endl;
        }
        else if (temp->dataType == "Course")
        {
            Course *c = (Course *)temp->data;
            cout << index++ << ". [Course] ID: " << c->course_id << " | Name: " << c->course_name
                 << " | Teacher: " << c->teacher_id << " | Credits: " << c->credits << endl;
        }
        else if (temp->dataType == "Enrollment")
        {
            Enrollment *e = (Enrollment *)temp->data;
            cout << index++ << ". [Enrollment] ID: " << e->enrollment_id << " | Student: " << e->student_id
                 << " | Course: " << e->course_id << " | Status: " << e->status << endl;
        }
        else if (temp->dataType == "User")
        {
            User *u = (User *)temp->data;
            cout << index++ << ". [User] ID: " << u->pending_id << " | Name: " << u->name
                 << " | Username: " << u->username << endl;
        }
        temp = temp->next;
    }
}

// ====================== CLEANUP ======================

void deleteDataList(dataList *dl)
{
    DataNode *temp = dl->head;
    while (temp != nullptr)
    {
        DataNode *next = temp->next;
        delete (void *)temp->data;
        delete temp;
        temp = next;
    }
    dl->head = nullptr;
    dl->tail = nullptr;
    dl->n = 0;
}