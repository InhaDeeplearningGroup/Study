//
// Created by Minkyu Lee on 2018. 2. 25..
//

#ifndef QUEUE_CIRCLEARRAYQUEUE_H
#define QUEUE_CIRCLEARRAYQUEUE_H


struct ArrayQueue;

struct ArrayQueue *Queue(int size);

int IsEmptyQueue(struct ArrayQueue *Q);

int IsFullQueue(struct ArrayQueue *Q);

int QueueSize(struct ArrayQueue *Q);

void EnQueue(struct ArrayQueue *Q, int data);

int DeQueue(struct ArrayQueue *Q);

void DeleteQueue(struct ArrayQueue *Q);

void CircleArrayQueueMain();

#endif //QUEUE_CIRCLEARRAYQUEUE_H
