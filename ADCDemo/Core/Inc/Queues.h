#ifndef DEMO_2_QUEUES_H
#define DEMO_2_QUEUES_H

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef float ElementType;

struct QueueRecord{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);

#endif
