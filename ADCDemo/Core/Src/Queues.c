#include <stdlib.h>
#include <stdio.h>

#include "Queues.h"

#define MinQueueSize (5)

int IsEmpty(Queue Q){
    return Q->Size == 0;
}

int IsFull(Queue Q){
    return Q->Capacity == Q->Size;
}

Queue CreateQueue(int MaxElements){
    Queue Q;

    if(MaxElements < MinQueueSize){
        printf("Queue size is too small");
    }

    Q = malloc(sizeof(struct QueueRecord));
    if(Q == NULL){
        printf("Out of space!!!");
    } else {
        Q->Array = malloc(sizeof(ElementType) * MaxElements);
        if(Q->Array == NULL){
            printf("Out of space!!!");
        } else {
            Q->Capacity = MaxElements;
            MakeEmpty(Q);
        }
    }

    return Q;
}

void DisposeQueue(Queue Q){
    if(Q != NULL){
        free(Q->Array);
        free(Q);
    }
}

void MakeEmpty(Queue Q){
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

static int Succ(int Value, Queue Q){
    if(++Value == Q->Capacity)
        Value = 0;
    return Value;
}

void Enqueue(ElementType X, Queue Q){
    if(IsFull(Q))
        printf("Full queue");
    else {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

ElementType Front(Queue Q){
    if(IsEmpty(Q))
        printf("Empty queue");
    else
        return Q->Array[Q->Front];

    return 0;       
}

void Dequeue(Queue Q){
    if(IsEmpty(Q))
        printf("Empty queue");
    else {
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

ElementType FrontAndDequeue(Queue Q) {
    ElementType Tmp = Front(Q);
    Dequeue(Q);

    return Tmp;
}
