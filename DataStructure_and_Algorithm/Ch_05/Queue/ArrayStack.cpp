//
// Created by Minkyu Lee on 2018. 2. 27..
//

#include <iostream>

struct ArrayStack{
    int top;
    int capacity;
    int *array;
};

struct ArrayStack *CreateStack(int size){
    struct ArrayStack *S = (ArrayStack *) malloc(sizeof(struct ArrayStack));
    if(!S)
        return NULL;
    S->capacity = size;
    S->top = -1;
    S->array = (int *) malloc(S->capacity * sizeof(int));
    if(!S->array)
        return NULL;
    return S;
}

int IsEmptyStack(struct ArrayStack *S){
    return (S->top == -1);
}

int IsFullStack(struct ArrayStack *S){
    return (S->top == S->capacity - 1);
}

void Push(struct ArrayStack *S, int data){
    if(IsFullStack(S))
        printf("Stack Overflow\n");
    else
        S->array[++S->top] = data;
}

int Pop(struct ArrayStack *S){
    if(IsEmptyStack(S)){
        printf("Stack is Empty\n");
        return 0;
    }
    else
        return (S->array[S->top--]);
}

void DeleteStack(struct ArrayStack *S){
    if(S){
        if(S->array)
            free(S->array);
        free(S);
    }
}

void ArrayStackMain(){
    int out1, out2, out3, out4;
    ArrayStack *S = NULL;
    S = CreateStack(10);

    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    Push(S, 4);

    out1 = Pop(S);
    out2 = Pop(S);
    printf("out1 = %d, out2 = %d\n", out1, out2);

    DeleteStack(S);
}

struct Queue{
    struct ArrayStack *S1;
    struct ArrayStack *S2;
};

struct Queue *CreateQueueUsingStack(int size){
    struct Queue *Q = (Queue *) malloc(sizeof(struct Queue));

    Q->S1 = (ArrayStack *) malloc(sizeof(struct ArrayStack));
    Q->S1->capacity = size;
    Q->S1->top = -1;
    Q->S1->array = (int *) malloc(Q->S1->capacity * sizeof(int));

    Q->S2 = (ArrayStack *) malloc(sizeof(struct ArrayStack));
    Q->S2->capacity = size;
    Q->S2->top = -1;
    Q->S2->array = (int *) malloc(Q->S2->capacity * sizeof(int));

    return Q;
}

void EnQueueStack(struct Queue *Q, int data){
    Push(Q->S1, data);
}

int DeQueueStack(struct Queue *Q){
    if(IsEmptyStack(Q->S2)){
        while(Q->S1->top != 0)
            Push(Q->S2, Pop(Q->S1));
        return Pop(Q->S1);
    }
    else{
        return Pop(Q->S2);
    }
}

void QueueStackMain(){
    int out1, out2;
    struct Queue *Q = NULL;
    Q = CreateQueueUsingStack(10);
    EnQueueStack(Q, 1);
    EnQueueStack(Q, 2);
    EnQueueStack(Q, 3);
    EnQueueStack(Q, 4);
    EnQueueStack(Q, 5);
    EnQueueStack(Q, 6);

    out1 = DeQueueStack(Q);
    out2 = DeQueueStack(Q);
    out1 = DeQueueStack(Q);
    out2 = DeQueueStack(Q);
    printf("out1 = %d, out2 = %d\n", out1, out2);
}