//
// Created by Minkyu Lee on 2018. 2. 25..
//

#ifndef QUEUE_DYNARRAYQUEUE_H
#define QUEUE_DYNARRAYQUEUE_H

struct DynArrayQueue;

struct DynArrayQueue *CreateDynQueue();

int IsEmptyDynQueue(struct DynArrayQueue *Q);

int IsFullDynQueue(struct DynArrayQueue *Q);

int QueueSize(struct DynArrayQueue *Q);

void ResizeQueue(struct DynArrayQueue *Q);

void DynEnQueue(struct DynArrayQueue *Q, int data);

int DynDeQueue(struct DynArrayQueue *Q);

void DeleteDynQueue(struct DynArrayQueue *Q);

void DynArrayQueueMain();

#endif //QUEUE_DYNARRAYQUEUE_H
