//
// Created by Minkyu Lee on 2018. 2. 25..
//
#include <iostream>

struct ArrayQueue{
    int front, rear;
    int capacity;
    int *array;
};

struct ArrayQueue *Queue(int size){
    struct ArrayQueue *Q;
    Q = (ArrayQueue *) malloc(sizeof(struct ArrayQueue));
    if(!Q)
        return NULL;
    Q->capacity = size;
    Q->front = Q->rear = -1;
    Q->array = (int *) malloc(Q->capacity * sizeof(int));
    if(!Q->array)
        return NULL;
    return Q;
}

int IsEmptyQueue(struct ArrayQueue *Q){
    return (Q->front == -1);
}

int IsFullQueue(struct ArrayQueue *Q){
    return((Q->rear + 1) % Q->capacity == Q->front);
}

int QueueSize(struct ArrayQueue *Q){
    return (Q->capacity - Q->front + Q->rear + 1) % Q->capacity;
}

void EnQueue(struct ArrayQueue *Q, int data){
    if(IsFullQueue(Q))
        printf("Queue Overflow");
    else{
        Q->rear = (Q->rear + 1) % Q->capacity;
        Q->array[Q->rear] = data;
        if(Q->front == -1)
            Q->front = Q->rear;
    }
}

int DeQueue(struct ArrayQueue *Q){
    int data = 0;
    if(IsEmptyQueue(Q)){
        printf("Queue is Empty");
        return 0;
    }
    else{
        data = Q->array[Q->front];
        if(Q->front == Q->rear)
            Q->front = Q->rear = -1;
        else
            Q->front = (Q->front + 1) % Q->capacity;
    }
    return data;
}

void DeleteQueue(struct ArrayQueue *Q){
    if(Q){
        if(Q->array)
            free(Q->array);
        free(Q);
    }
}

void CircleArrayQueueMain(){
    int out1, out2, out3, out4;
    struct ArrayQueue *Q;
    Q = Queue(10);
    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);
    EnQueue(Q, 6);
    printf("Queue size : %d\n", QueueSize(Q));

    out1 = DeQueue(Q);
    out2 = DeQueue(Q);
    out3 = DeQueue(Q);
    out4 = DeQueue(Q);
    printf("out1 = %d, out2 = %d, out3 = %d, out4 = %d\n", out1, out2, out3, out4);
    printf("Queue size : %d\n", QueueSize(Q));

    EnQueue(Q, 7);
    EnQueue(Q, 8);
    EnQueue(Q, 9);
    printf("Queue size : %d\n", QueueSize(Q));

    EnQueue(Q, 10);
    EnQueue(Q, 11);
    EnQueue(Q, 12);
    printf("Queue size : %d\n", QueueSize(Q));

    EnQueue(Q, 13);
    EnQueue(Q, 14);
    printf("Queue size : %d\n", QueueSize(Q));
    EnQueue(Q, 15);
    printf("Queue size : %d\n", QueueSize(Q));

    DeleteQueue(Q);
}