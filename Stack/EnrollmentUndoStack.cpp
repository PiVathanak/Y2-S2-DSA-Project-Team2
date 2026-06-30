#pragma once

#include<iostream>
#include<string>
using namespace std;

struct UndoRecord
{
    string enrollmentID;
    string studentID;
    string courseID;
    string dropDate;
    void* ptr;
};

struct Element
{
    UndoRecord data;
    Element *next;
};

struct Stack
{
    int n;
    Element *top;
};

Stack *createStack()
{
    Stack *s = new Stack;
    s->n = 0;
    s->top = nullptr;
    return s;
}

bool isEmpty(Stack *s)
{
    return s->n == 0;
}

void push(Stack *s, UndoRecord record)
{
    Element *e = new Element;

    e->data = record;
    e->next = s->top;

    s->top = e;
    s->n++;
}

void pop(Stack *s)
{
    if (isEmpty(s))
    {
        cout << "Stack is empty" << endl;
        return;
    }

    Element *e = s->top;

    s->top = s->top->next;

    delete e;

    s->n--;
}

UndoRecord peek(Stack *s)
{
    if (isEmpty(s))
    {
        cout << "Stack is empty" << endl;

        UndoRecord empty;
        empty.enrollmentID = "";
        empty.studentID = "";
        empty.courseID = "";
        empty.dropDate = "";
        empty.ptr = nullptr;

        return empty;
    }

    return s->top->data;
}

int getSize(Stack *s)
{
    return s->n;
}

void clearStack(Stack *s)
{
    while (!isEmpty(s))
    {
        pop(s);
    }
}

void display(Stack *s)
{
    if (isEmpty(s))
    {
        cout << "Stack is empty" << endl;
        return;
    }

    Element *e = s->top;

    cout << "----- Undo Stack -----" << endl;

    while (e != nullptr)
    {
        cout << "Enrollment ID : " << e->data.enrollmentID << endl;
        cout << "Student ID  : " << e->data.studentID << endl;
        cout << "Course ID  : " << e->data.courseID << endl;

        cout << "----------------------" << endl;

        e = e->next;
    }
}
string getActiveStudentID()
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/Students.csv");

    for (const auto &fields : rows)
    {
        if (fields.size() > 6 && fields[6] == "Online")
        {
            return fields[0];
        }
    }

    return "";
}
void displayPendingEnrollmentsForStudent(string studentID, string title)
{
    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/PendingEnrollment.csv");

    bool found = false;

    cout << "\n"
         << title << "\n\n";

    for (const auto &fields : rows)
    {
        if (fields.size() < 3)
        {
            continue;
        }

        if (fields[1] == studentID)
        {
            found = true;

            cout << "Enrollment ID : " << fields[0] << endl;
            cout << "Course ID     : " << fields[2] << endl;
            cout << "-----------------------------" << endl;
        }
    }

    if (!found)
    {
        cout << "You have no pending enrollments." << endl;
    }
}

void displayMyEnrollments(string studentID)
{
    displayPendingEnrollmentsForStudent(studentID, "===== My Pending Enrollments =====");
}
void restoreToCSV(UndoRecord record)
{
    ifstream check("../DataBase/PendingEnrollment.csv");
    bool hasContent = false;
    string firstLine;

    if (getline(check, firstLine))
    {
        hasContent = true;
    }

    check.close();

    ofstream file(
        "../DataBase/PendingEnrollment.csv",
        ios::app);

    if (!file)
    {
        cout << "Cannot open PendingEnrollment.csv" << endl;
        return;
    }

    if (!hasContent)
    {
        file << "enrollment_id,student_id,course_id" << endl;
    }

    file
        << record.enrollmentID << ","
        << record.studentID << ","
        << record.courseID
        << endl;

    file.close();
}
void cancelEnrollment(
    Stack *undoStack,
    string currentStudentID,
    string enrollmentID)
{

    vector<vector<string>> rows = CSVReader::readCSVRows("../DataBase/PendingEnrollment.csv");

    vector<vector<string>> updatedRows;
    bool found = false;

    for (const auto &fields : rows)
    {
        if (fields.size() < 3)
        {
            continue;
        }

        UndoRecord record;
        record.enrollmentID = fields[0];
        record.studentID = fields[1];
        record.courseID = fields[2];

        if (record.enrollmentID == enrollmentID &&
            record.studentID == currentStudentID)
        {
            push(undoStack, record);
            found = true;
            continue;
        }

        updatedRows.push_back(fields);
    }

    ofstream out("../DataBase/PendingEnrollment.csv");

    if (!out)
    {
        cout << "Cannot open PendingEnrollment.csv" << endl;
        return;
    }

    if (!rows.empty())
    {
        out << "enrollment_id,student_id,course_id" << endl;
    }

    for (const auto &row : updatedRows)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            if (i > 0)
            {
                out << ",";
            }
            out << row[i];
        }
        out << endl;
    }

    out.close();

    if (found)
    {
        cout << "Enrollment Cancelled" << endl;
    }
    else
    {
        cout << "Enrollment ID Not Found" << endl;
    }
}
void undoEnrollment(Stack *s)
{

    if (isEmpty(s))
    {
        cout << "Nothing to undo" << endl;
        return;
    }

    UndoRecord record = peek(s);

    restoreToCSV(record);

    cout << "\nEnrollment Restored" << endl;
    cout << "Enrollment ID : " << record.enrollmentID << endl;
    cout << "Student ID    : " << record.studentID << endl;
    cout << "Course ID     : " << record.courseID << endl;

    pop(s);
}

void testUndoStack(){

    Stack *undoStack = createStack();

    string currentStudentID = getActiveStudentID();

    if (currentStudentID == "")
    {
        cout << "No student is currently logged in." << endl;
        return 0;
    }

    cout << "Current Student: " << currentStudentID << endl;

    displayMyEnrollments(currentStudentID);

    string enrollmentID;

    cout << "\nEnter Enrollment ID to cancel: ";
    cin >> enrollmentID;

    cancelEnrollment(
        undoStack,
        currentStudentID,
        enrollmentID);

    char choice;

    cout << "\nDo you want to undo? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        undoEnrollment(undoStack);
    }

    displayPendingEnrollmentsForStudent(currentStudentID, "===== Current Pending Enrollments =====");

    clearStack(undoStack);

    delete undoStack;
    
}