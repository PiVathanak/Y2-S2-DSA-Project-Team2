#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct UndoRecord
{
    string enrollmentID;
    string studentID;
    string courseID;
    string status;
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
        empty.status = "";

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
        cout << "Enrollment ID : " << e->data.courseID << endl;
        cout << "Student ID  : " << e->data.studentID << endl;
        cout << "Course ID  : " << e->data.courseID << endl;

        cout << "----------------------" << endl;

        e = e->next;
    }
}
string getActiveStudentID()
{

    ifstream file("../DataBase/students.csv");

    if (!file)
    {
        return "";
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {

        stringstream ss(line);

        string studentID;
        string name;
        string email;
        string status;

        getline(ss, studentID, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, status);

        if (status == "Active")
        {
            file.close();
            return studentID;
        }
    }

    file.close();
    return "";
}
void displayMyEnrollments(string studentID)
{

    ifstream file("../DataBase/PendingEnrollment.csv");

    string line;

    cout << "\n===== My Pending Enrollments =====\n\n";

    while (getline(file, line))
    {

        stringstream ss(line);

        string enrollmentID;
        string sid;
        string courseID;
        string status;

        getline(ss, enrollmentID, ',');
        getline(ss, sid, ',');
        getline(ss, courseID, ',');
        getline(ss, status);

        if (sid == studentID)
        {
            cout << enrollmentID << " | "
                 << courseID << " | "
                 << status << endl;
        }
    }

    file.close();
}
void restoreToCSV(UndoRecord record)
{

    ofstream file(
        "../DataBase/PendingEnrollment.csv",
        ios::app);

    if (!file)
    {
        cout << "Cannot open PendingEnrollment.csv" << endl;
        return;
    }

    file
        << record.enrollmentID << ","
        << record.studentID << ","
        << record.courseID << ","
        << record.status
        << endl;

    file.close();
}
void cancelEnrollment(
    Stack *undoStack,
    string currentStudentID,
    string enrollmentID)
{

    ifstream file("../DataBase/PendingEnrollment.csv");

    vector<string> rows;

    string line;

    bool found = false;

    while (getline(file, line))
    {

        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        UndoRecord record;

        getline(ss, record.enrollmentID, ',');
        getline(ss, record.studentID, ',');
        getline(ss, record.courseID, ',');
        getline(ss, record.status);

        if (record.enrollmentID == enrollmentID &&
            record.studentID == currentStudentID)
        {

            push(undoStack, record);

            found = true;

            continue;
        }

        rows.push_back(line);
    }

    file.close();

    ofstream out("../DataBase/PendingEnrollment.csv");

    for (string row : rows)
    {
        out << row << endl;
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

int main()
{

    Stack *undoStack = createStack();

    cout << "\n===== Pending Enrollments =====\n"
         << endl;

    ifstream file("../DataBase/PendingEnrollment.csv");

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

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

    cout << "\n===== Current Pending Enrollments =====\n"
         << endl;

    ifstream file2("../DataBase/PendingEnrollment.csv");

    while (getline(file2, line))
    {
        cout << line << endl;
    }

    file2.close();

    clearStack(undoStack);

    delete undoStack;

    return 0;
}