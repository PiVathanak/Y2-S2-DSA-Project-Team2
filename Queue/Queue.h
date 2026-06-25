#ifndef QUEUE_H
#define QUEUE_H

#include "PendingEnrollment.h"

struct Element {
    PendingEnrollment data;
    Element* next;
};

struct Queue {
    int n;
    Element* front;
    Element* rear;
};

// Queue operations (teacher's style)
Queue* createQueue();
void enqueue(Queue* q, const PendingEnrollment& data);
PendingEnrollment dequeue(Queue* q);
bool isEmpty(const Queue* q);
int getSize(const Queue* q);
PendingEnrollment getFront(const Queue* q);
PendingEnrollment getRear(const Queue* q);
void displayQueue(const Queue* q);
void deleteQueue(Queue* q);

#endif