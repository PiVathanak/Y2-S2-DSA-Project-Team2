#include "Queue.h"
#include <iostream>

Queue* createQueue() {
    Queue* q = new Queue;
    q->n = 0;
    q->front = nullptr;
    q->rear = nullptr;
    return q;
}

void enqueue(Queue* q, const PendingEnrollment& data) {
    Element* e = new Element;
    e->data = data;
    e->next = nullptr;
    
    if (q->n == 0) {
        q->front = e;
        q->rear = e;
    } else {
        q->rear->next = e;
        q->rear = e;
    }
    q->n++;
}

PendingEnrollment dequeue(Queue* q) {
    if (isEmpty(q)) {
        std::cout << "Queue is empty\n";
        return PendingEnrollment();
    }
    
    PendingEnrollment value = q->front->data;
    Element* e = q->front;
    q->front = e->next;
    
    if (q->front == nullptr) {
        q->rear = nullptr;
    }
    
    delete e;
    q->n--;
    return value;
}

bool isEmpty(const Queue* q) {
    return q->n == 0;
}

int getSize(const Queue* q) {
    return q->n;
}

PendingEnrollment getFront(const Queue* q) {
    if (isEmpty(q)) {
        std::cout << "Queue is empty\n";
        return PendingEnrollment();
    }
    return q->front->data;
}

PendingEnrollment getRear(const Queue* q) {
    if (isEmpty(q)) {
        std::cout << "Queue is empty\n";
        return PendingEnrollment();
    }
    return q->rear->data;
}

void displayQueue(const Queue* q) {
    if (isEmpty(q)) {
        std::cout << "Queue is empty\n";
        return;
    }
    
    std::cout << "\n=== Pending Enrollments (FIFO Order) ===" << std::endl;
    std::cout << "Position\tEnrollment ID\tStudent ID\tCourse ID" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    Element* e = q->front;
    int pos = 1;
    while (e != nullptr) {
        std::cout << pos++ << "\t\t"
                  << e->data.enrollmentId << "\t\t"
                  << e->data.studentId << "\t\t"
                  << e->data.courseId << std::endl;
        e = e->next;
    }
    std::cout << "=============================================" << std::endl;
    std::cout << "Total: " << q->n << " pending" << std::endl;
}

void deleteQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    delete q;
}