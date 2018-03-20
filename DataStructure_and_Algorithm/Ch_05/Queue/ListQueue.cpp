//
// Created by Minkyu Lee on 2018. 2. 25..
//

#include <iostream>

struct ListNode{
    int data;
    struct ListNode *next;
};

struct Queue{
    struct ListNode *front;
    struct ListNode *rear;
};

struct Queue *CreateQueue(){
    struct Queue *Q;
    struct ListNode *temp;
    Q = (Queue *) malloc(sizeof(struct Queue));
    if(!Q)
        return NULL;
    temp = (ListNode *) malloc(sizeof(struct ListNode));
    Q->front = Q->rear = NULL;
    return Q;
}

int IsEmptyQueue(struct Queue *Q){
    return (Q->front == NULL);
}

struct Queue *EnQueue(struct Queue *Q, int data){
    struct ListNode *newNode;
    newNode = (ListNode *) malloc(sizeof(struct ListNode));
    if(!newNode)
        return NULL;
    newNode->data = data;
    newNode->next = NULL;
    Q->rear->next = newNode;
    Q->rear = newNode;
    if(Q->front == NULL)
        Q->front = Q->rear;
}

int DeQueue(struct Queue *Q){
    int data = 0;
    struct ListNode *temp;
    if(IsEmptyQueue(Q)){
        printf("Queue is empty\n");
        return 0;
    }
    else{
        temp = Q->front;
        data = Q->front->data;
        Q->front = Q->front->next;
        free(temp);
    }
    return data;
}

void DeleteQueue(struct Queue *Q){
    struct Queue *temp;
    while(Q){
        temp = Q;
    }
}