#include <iostream>
using namespace std;

struct ListNode{
    int data;
    struct ListNode *next;
};

struct DLLNode{
    int data;
    struct DLLNode *next;
    struct DLLNode *prev;
};

struct CLLNode{
    int data;
    struct CLLNode *next;
};

int ListLength(struct ListNode *head){
    struct ListNode *current = head;
    int count = 0;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

void InsertInLinkedList(struct ListNode **head, int data, int position){
    int k = 1;
    struct ListNode *p, *q, *newNode;
    newNode = (ListNode *) malloc(sizeof(struct ListNode));
    if(!newNode){
        printf("Memory Error");
        return;
    }
    newNode->data = data;
    p = *head;

    if(position == 1){
        newNode->next = p;
        *head = newNode;
    }
    else{
        while((p != NULL) && (k <= position - 1)){
            k++;
            q = p;
            p = p->next;
        }
        if(p == NULL){
            q->next = newNode;
            newNode->next = NULL;
        }
        else{
            q->next = newNode;
            newNode->next = p;
        }
    }
}

//void DeleteNodeFromLinkedList(struct ListNode **head, int position){
//    int k = 1;
//    struct ListNode *p, *q;
//    if(*head == NULL){
//        printf("List Empty");
//        return;
//    }
//    p = *head;
//
//    if(position == 1){
//        q = *head;
//        *head = q->next;
//        free(q);
//        return;
//    }
//    else{
//        while((p != NULL) && (k <= position - 1)){
//            k++;
//            q = p;
//            p = p->next;
//        }
//        if(p == NULL)
//            printf("Position does not exist.");
//        else{
//            q->next = p->next;
//            free(p);
//        }
//    }
//}

int DeleteNodeFromLinkedList(struct ListNode **head, int position){
    int k = 1;
    int data;
    struct ListNode *p, *q;
    if(*head == NULL){
        printf("List Empty");
        return 0;
    }
    p = *head;

    if(position == 1){
        q = *head;
        data = q->data;
        *head = q->next;
        free(q);
        return data;
    }
    else{
        while((p != NULL) && (k <= position - 1)){
            k++;
            q = p;
            p = p->next;
        }
        if(p == NULL)
            printf("Position does not exist.");
        else{
            q->next = p->next;
            free(p);
        }
    }
}

void DeleteLinkedList(struct ListNode **head){
    struct ListNode *auxilaryNode, *iterator;
    iterator = *head;
    while(iterator){
        auxilaryNode = iterator->next;
        free(iterator);
        iterator = auxilaryNode;
    }
    *head = NULL;
}

void DLLInsert(struct DLLNode **head, int data, int position){
    int k = 1;
    struct DLLNode *temp, *newNode;
    newNode = (struct DLLNode *) malloc(sizeof(struct DLLNode));
    if(!newNode){
        printf("Memory Error!");
        return;
    }

    newNode->data = data;
    if(position == 1){
        newNode->next = *head;
        newNode->prev = NULL;
        temp = *head;
        if(temp != NULL)
            temp->prev = newNode;
        *head = newNode;
        return;
    }

    temp = *head;
    while((k <= position - 1) && temp->next != NULL){
        temp = temp->next;
        k++;
    }
    if(temp->next == NULL){
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
    }
    else{
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
    return;
}

void DLLDelete(struct DLLNode **head, int position){
    struct DLLNode *temp, *temp2;
    temp = *head;
    int k = 1;
    if(*head == NULL){
        printf("List is empty");
        return;
    }
    if(position == 1){
        temp2 = *head; // TODO : change
        *head = temp2->next; // *head = *head->next
        if(*head != NULL)
            temp2->prev = NULL;
        free(temp);
        return;
    }
    while((k <= position - 1) && temp->next != NULL){ // TODO : change '<' -----> '<='
        temp = temp->next;
        k++;
    }
    if(temp->next == NULL){
        temp2 = temp->prev;
        temp2->next = NULL;
        free(temp);
    }
    else{
        temp2 = temp->prev;
        temp2->next = temp->next;
        temp->next->prev = temp2;
        free(temp);
    }
    return;
}

int CircularListLength(struct CLLNode *head){
    struct CLLNode *current = head;
    int count = 0;
    if(head == NULL)
        return 0;
    do{
        current = current->next;
        count++;
    } while(current != head);
    return count;
}

void PrintCircularListData(struct CLLNode *head){
    struct CLLNode *current = head;
    if(head == NULL)
        return;
    do{
        printf("%d ", current->data);
        current = current->next;
    } while(current != head);
    printf("\n");
}

void InsertAtEndInCLL(struct CLLNode **head, int data){
    struct CLLNode *current = *head;
    struct CLLNode *newNode = (struct CLLNode*)(malloc(sizeof(struct CLLNode)));
    if(!newNode){
        printf("Memory Error");
        return;
    }
    newNode->data = data;
    if(current == NULL){
        newNode->next = newNode;
        *head = newNode;
        return;
    }
    while(current->next != *head)
        current = current->next;
    newNode->next = newNode;
    newNode->next = *head; // TODO : change
    current->next = newNode;
}

void InsertAtBeginInCLL(struct CLLNode **head, int data){
    struct CLLNode *current = *head;
    struct CLLNode *newNode = (struct CLLNode*)(malloc(sizeof(struct CLLNode)));
    if(!newNode){
        printf("Memory Error");
        return;
    }
    newNode->data = data;
    if(current == NULL){
        newNode->next = newNode;
        *head = newNode;
        return;
    }
    while(current->next != *head)
        current = current->next;
    newNode->next = newNode;
    newNode->next = *head;
    current->next = newNode;
    *head = newNode;

    return;
}

void DeleteLastNodeFromCLL(struct CLLNode **head){
    struct CLLNode *temp = *head;
    struct CLLNode *current = *head;
    if(*head == NULL){
        printf("List Empty");
        return;
    }
    while(current->next != *head){
        temp = current;
        current = current->next;
    }
    temp->next = *head; // TODO : add this line
    free(current);
    return;
}

void DeleteFrontNodeFromCLL(struct CLLNode **head){
    struct CLLNode *temp = *head;
    struct CLLNode *current = *head;
    if(*head == NULL){
        printf("List Empty");
        return;
    }
    while(current->next != *head)
        current = current->next;
    current->next = temp->next; // TODO : change variable : *head -> temp
    *head = current->next;
    free(temp);
    return;
}

void stackpush(ListNode **head, int data){
    const int STACK_MODE = 1;
    InsertInLinkedList(head, data, STACK_MODE);
}

int stackpop(ListNode **head){
    int data;
    const int STACK_MODE = 1;
    data = DeleteNodeFromLinkedList(head, STACK_MODE);

    return data;
}

struct ListNode *NthNodeFromEnd(struct ListNode *head, int NthNode){
    struct ListNode *pTemp = NULL, *pNthNode = NULL;
    int count = 0;
    pNthNode = head;
    for(pTemp = head; pTemp != NULL;){
        count++;
        if(NthNode - count == 0)
            pNthNode = head;
        else if(NthNode - count < 0)
            pNthNode = pNthNode->next;
        pTemp = pTemp->next;
    }
    if(pNthNode)
        return pNthNode;
    return NULL;
}

int main(){
    /*
    // Singly Linked List Example //
    ListNode *head = NULL;

    InsertInLinkedList(&head, 10, 1);
    InsertInLinkedList(&head, 5, 2);
    InsertInLinkedList(&head, 1022, 3);
    InsertInLinkedList(&head, 52, 4);
    InsertInLinkedList(&head, 107, 5);
    InsertInLinkedList(&head, 1, 6);
    printf("%d\n", head->data);
    printf("%d\n", ListLength(head));

    DeleteNodeFromLinkedList(&head, 1);
    printf("%d\n", head->data);
    DeleteNodeFromLinkedList(&head, 3);
    printf("%d\n", ListLength(head));

    DeleteLinkedList(&head);
    */

    /*
    // Doubly Linked List Example //
    DLLNode *head = NULL;
    DLLInsert(&head, 10, 1);
    DLLInsert(&head, 15, 2);
    DLLInsert(&head, 125, 3);
    DLLInsert(&head, 103, 4);
    DLLInsert(&head, 1511, 5);
    DLLInsert(&head, 12765, 6);
    printf("%d\n", head->data);
    printf("%d\n", head->next->data);

    DLLDelete(&head, 1);
    printf("%d\n", head->data);
    DLLDelete(&head, 3);
    printf("%d\n", head->data);
    */

    /*
    // Circular Linked List Example //
    CLLNode *head= NULL;
    InsertAtEndInCLL(&head, 25650);
    InsertAtBeginInCLL(&head, 10);
    InsertAtBeginInCLL(&head, 102);
    InsertAtBeginInCLL(&head, 105);
    InsertAtEndInCLL(&head, 20);
    InsertAtEndInCLL(&head, 120);
    InsertAtEndInCLL(&head, 250);
    PrintCircularListData(head);
    printf("%d\n", CircularListLength(head));

    DeleteLastNodeFromCLL(&head);
    DeleteFrontNodeFromCLL(&head);
    PrintCircularListData(head);
    printf("%d\n", CircularListLength(head));
    */

    /*
    // Stack using Singly Linked List (LIFO)//
    ListNode *head = NULL;

    stackpush(&head, 10);
    stackpush(&head, 15);
    stackpush(&head, 25);
    stackpush(&head, 35);
    printf("%d\n", stackpop(&head));
    printf("%d\n", stackpop(&head));
    printf("%d\n", stackpop(&head));
    */

    // Find the nth node at the end //
    ListNode *head = NULL;
    ListNode *nthNode = NULL;

    InsertInLinkedList(&head, 10, 1);
    InsertInLinkedList(&head, 5, 2);
    InsertInLinkedList(&head, 1022, 3);
    InsertInLinkedList(&head, 52, 4);
    InsertInLinkedList(&head, 107, 5);
    InsertInLinkedList(&head, 1, 6);
    printf("%d\n", head->data);
    printf("%d\n", ListLength(head));

    nthNode = NthNodeFromEnd(head, 3);
    printf("%d\n", nthNode->data);

    return 0;
}
