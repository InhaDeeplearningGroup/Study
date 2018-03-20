//
// Created by Minkyu Lee on 2018. 2. 27..
//

#ifndef QUEUE_ARRAYSTACK_H
#define QUEUE_ARRAYSTACK_H

//
// Created by Minkyu Lee on 2018. 2. 27..
//

#include <iostream>

struct ArrayStack;

struct ArrayStack *CreateStack();

int IsEmptyStack(struct ArrayStack *S);

int IsFullStack(struct ArrayStack *S);

void Push(struct ArrayStack *S, int data);

int Pop(struct ArrayStack *S);

void DeleteStack(struct ArrayStack *S);

void ArrayStackMain();

struct Queue;

struct Queue *CreateQueueUsingStack(int size);

void EnQueueStack(struct Queue *Q, int data);

int DeQueueStack(struct Queue *Q);

void QueueStackMain();

#endif //QUEUE_ARRAYSTACK_H
