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
                    else if (field == "username")
                        s->username = newValue;
                    else if (field == "email")
                        s->email = newValue;
                    else if (field == "password")
                        s->password = newValue;
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
                    else if (field == "course_id")
                        t->course_id = newValue;
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
                    else if (field == "teacher_id")
                        c->teacher_id = newValue;
                    else if (field == "credits")
                        c->credits = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "Enrollment")
            {
                Enrollment *e = (Enrollment *)temp->data;
                if (e->enrollment_id == id)
                {
                    if (field == "student_id")
                        e->student_id = newValue;
                    else if (field == "course_id")
                        e->course_id = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "PendingEnrollment")
            {
                PendingEnrollment *p = (PendingEnrollment *)temp->data;
                if (p->enrollment_id == id)
                {
                    if (field == "student_id")
                        p->student_id = newValue;
                    else if (field == "course_id")
                        p->course_id = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "Admin")
            {
                Admin *a = (Admin *)temp->data;
                if (a->admin_id == id)
                {
                    if (field == "username")
                        a->username = newValue;
                    else if (field == "password")
                        a->password = newValue;
                    cout << "Updated successfully!" << endl;
                    return;
                }
            }
            else if (dataType == "PendingUser")
            {
                PendingUser *u = (PendingUser *)temp->data;
                if (u->student_id == id)
                {
                    if (field == "name")
                        u->name = newValue;
                    else if (field == "username")
                        u->username = newValue;
                    else if (field == "email")
                        u->email = newValue;
                    else if (field == "password")
                        u->password = newValue;
                    else if (field == "status")
                        u->status = newValue;
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
            else if (dataType == "PendingEnrollment")
            {
                PendingEnrollment *p = (PendingEnrollment *)temp->data;
                foundId = (p->enrollment_id == id);
            }
            else if (dataType == "Admin")
            {
                Admin *a = (Admin *)temp->data;
                foundId = (a->admin_id == id);
            }
            else if (dataType == "PendingUser")
            {
                PendingUser *u = (PendingUser *)temp->data;
                foundId = (u->student_id == id);
            }

            if (foundId)
            {
                if (prev == nullptr)
                {
                    dl->head = temp->next;
                    if (dl->n == 1)
                    {
                        dl->tail = nullptr;
                    }
                }
                else
                {
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
            cout << index++ << ". [Student] ID: " << s->student_id
                 << " | Name: " << s->name
                 << " | Username: " << s->username
                 << " | Email: " << s->email
                 << " | Password: " << s->password
                 << " | Status: " << s->status << endl;
        }
        else if (temp->dataType == "Teacher")
        {
            Teacher *t = (Teacher *)temp->data;
            cout << index++ << ". [Teacher] ID: " << t->teacher_id
                 << " | Name: " << t->name
                 << " | Course ID: " << t->course_id << endl;
        }
        else if (temp->dataType == "Course")
        {
            Course *c = (Course *)temp->data;
            cout << index++ << ". [Course] ID: " << c->course_id
                 << " | Name: " << c->course_name
                 << " | Teacher: " << c->teacher_id
                 << " | Credits: " << c->credits << endl;
        }
        else if (temp->dataType == "Enrollment")
        {
            Enrollment *e = (Enrollment *)temp->data;
            cout << index++ << ". [Enrollment] ID: " << e->enrollment_id
                 << " | Student: " << e->student_id
                 << " | Course: " << e->course_id << endl;
        }
        else if (temp->dataType == "PendingEnrollment")
        {
            PendingEnrollment *p = (PendingEnrollment *)temp->data;
            cout << index++ << ". [PendingEnrollment] ID: " << p->enrollment_id
                 << " | Student: " << p->student_id
                 << " | Course: " << p->course_id << endl;
        }
        else if (temp->dataType == "Admin")
        {
            Admin *a = (Admin *)temp->data;
            cout << index++ << ". [Admin] ID: " << a->admin_id
                 << " | Username: " << a->username
                 << " | Password: " << a->password << endl;
        }
        else if (temp->dataType == "PendingUser")
        {
            PendingUser *u = (PendingUser *)temp->data;
            cout << index++ << ". [PendingUser] ID: " << u->student_id
                 << " | Name: " << u->name
                 << " | Username: " << u->username
                 << " | Email: " << u->email
                 << " | Password: " << u->password
                 << " | Status: " << u->status << endl;
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