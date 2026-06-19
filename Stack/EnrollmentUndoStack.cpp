#include<iostream>
#include<string>
using namespace std;

struct UndoRecord{
    string studentID;
    string courseID;
    string dropDate;
};

struct Element{
    UndoRecord data;
    Element* next;
};

struct Stack{
    int n;
    Element* top;
};

Stack* createStack(){
    Stack* s = new Stack;
    s->n = 0;
    s->top = nullptr;
    return s;
}

bool isEmpty(Stack* s){
    return s->n == 0;
}

void push(Stack* s, UndoRecord record){
    Element* e = new Element;

    e->data = record;
    e->next = s->top;

    s->top = e;
    s->n++;
}

void pop(Stack* s){
    if(isEmpty(s)){
        cout<<"Stack is empty"<<endl;
        return;
    }

    Element* e = s->top;

    s->top = s->top->next;

    delete e;

    s->n--;
}

UndoRecord peek(Stack* s){
    if(isEmpty(s)){
        cout<<"Stack is empty"<<endl;

        UndoRecord empty;
        empty.studentID = "";
        empty.courseID = "";
        empty.dropDate = "";

        return empty;
    }

    return s->top->data;
}

int getSize(Stack* s){
    return s->n;
}

void clearStack(Stack* s){
    while(!isEmpty(s)){
        pop(s);
    }
}

void display(Stack* s){
    if(isEmpty(s)){
        cout<<"Stack is empty"<<endl;
        return;
    }

    Element* e = s->top;

    cout<<"----- Undo Stack -----"<<endl;

    while(e != nullptr){
        cout<<"Student ID : "<<e->data.studentID<<endl;
        cout<<"Course ID  : "<<e->data.courseID<<endl;
        cout<<"Drop Date  : "<<e->data.dropDate<<endl;
        cout<<"----------------------"<<endl;

        e = e->next;
    }
}

void undoEnrollment(Stack* s){
    if(isEmpty(s)){
        cout<<"Nothing to undo"<<endl;
        return;
    }

    UndoRecord record = peek(s);

    cout<<"\nUndo Enrollment"<<endl;
    cout<<"Student ID : "<<record.studentID<<endl;
    cout<<"Course ID  : "<<record.courseID<<endl;
    cout<<"Restored Successfully"<<endl;

    pop(s);
}

int main(){

    Stack* undoStack = createStack();

    UndoRecord r1;
    r1.studentID = "S001";
    r1.courseID = "C001";
    r1.dropDate = "2026-06-18";

    UndoRecord r2;
    r2.studentID = "S001";
    r2.courseID = "C002";
    r2.dropDate = "2026-06-18";

    UndoRecord r3;
    r3.studentID = "S002";
    r3.courseID = "C003";
    r3.dropDate = "2026-06-18";

    push(undoStack, r1);
    push(undoStack, r2);
    push(undoStack, r3);

    display(undoStack);

    cout<<"\nCurrent Size = "<<getSize(undoStack)<<endl;

    undoEnrollment(undoStack);

    cout<<"\nAfter Undo:\n"<<endl;

    display(undoStack);

    clearStack(undoStack);

    delete undoStack;

    return 0;
}