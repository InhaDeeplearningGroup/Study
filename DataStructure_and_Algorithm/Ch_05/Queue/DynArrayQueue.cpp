//
// Created by Minkyu Lee on 2018. 2. 25..
//
#include <iostream>

struct DynArrayQueue{
    int front, rear;
    int capacity;
    int *array;
};

struct DynArrayQueue *CreateDynQueue(){
    struct DynArrayQueue *Q = (DynArrayQueue *) malloc(sizeof(struct DynArrayQueue));
    if(!Q)
        return NULL;
    Q->capacity = 1;
    Q->front = Q->rear = -1;
    Q->array = (int *) malloc(Q->capacity * sizeof(int));
    if(!Q->array)
        return NULL;
    return Q;
}

int IsEmptyQueue(struct DynArrayQueue *Q){
    return (Q->front == - 1);
}

int IsFullQueue(struct DynArrayQueue *Q){
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

int QueueSize(struct DynArrayQueue *Q){
    int size;
    size = (Q->capacity - Q->front + Q->rear + 1) % Q->capacity;
    if (size == 0)
        return Q->capacity;
    return size;
}

void ResizeQueue(struct DynArrayQueue *Q){
    int size = Q->capacity;
    Q->capacity = Q->capacity * 2;
    Q->array = (int *) realloc(Q->array, Q->capacity);
    if(!Q->array){
        printf("Memory Error\n");
        return;
    }
    if(Q->front > Q->rear){
        for(int i = 0; i < Q->front; i++){
            Q->array[i+size] = Q->array[i];
        }
        Q->rear = Q->rear + size;
    }
}

void DynEnQueue(struct DynArrayQueue *Q, int data){
    if(IsFullQueue(Q))
        ResizeQueue(Q);
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->array[Q->rear] = data;
    if(Q->front == -1)
        Q->front = Q->rear;
}

int DynDeQueue(struct DynArrayQueue *Q){
    int data = 0;
    if(IsEmptyQueue(Q)){
        printf("Queue is Empty\n");
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

void DeleteQueue(struct DynArrayQueue *Q){
    if(Q){
        if(Q->array)
            free(Q->array);
        free(Q);
    }
}

void DynArrayQueueMain(){
    int out1, out2, out3, out4;
    DynArrayQueue *Q;

    Q = CreateDynQueue();
    DynEnQueue(Q, 1);
    DynEnQueue(Q, 2);
    DynEnQueue(Q, 3);
    DynEnQueue(Q, 4);
    DynEnQueue(Q, 5);
    DynEnQueue(Q, 6);
    DynEnQueue(Q, 7);
    DynEnQueue(Q, 8);
    printf("Queue size : %d\n", QueueSize(Q));

    out1 = DynDeQueue(Q);
    out2 = DynDeQueue(Q);
    out3 = DynDeQueue(Q);
    out4 = DynDeQueue(Q);
    printf("out1 = %d, out2 = %d, out3 = %d, out4 = %d\n", out1, out2, out3, out4);
    printf("Queue size : %d\n", QueueSize(Q));

//    DeleteQueue(Q);
}