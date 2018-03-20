#include <iostream>

struct Heap{ // 완전 트리 기반 내림차순 heap
    int *array;
    int count;
    int capacity;
    char* heap_type;
};

struct Heap *CreateHeap(int capacity, char* heap_type){ // Heap 생성 함수
    struct Heap *h = (struct Heap *) malloc(sizeof(struct Heap));
    if(h == NULL){
        printf("Memory Error");
        return NULL;
    }
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->array = (int *) malloc(sizeof(int) * h->capacity);
    if(h->array == NULL){
        printf("Memory Error");
        return NULL;
    }
    return h;
}

int Parent(struct Heap *h, int i){ // 부모 노드 index 출력
    if(i <= 0 || i >= h->count)
        return -1;
    return (i - 1) / 2;
}

int LeftChild(struct Heap *h, int i){ // left child index 출력
    int left = 2 * i + 1;
    if(left >= h->count)
        return -1;
    return left;
}

int RightChild(struct Heap *h, int i){ // right child index 출력
    int right = 2 * i + 2;
    if(right >= h->count)
        return -1;
    return right;
}

int GetMaximum(struct Heap *h){ // 최대값 출력. heap에서의 root 노드
    if(h->count == 0)
        return -1;
    return h->array[0];
}

void PercolateDown(struct Heap *h, int i){ // heap 속성에 위반 시, 재정렬, 책과 다름
    int l, r, max, temp;
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if(l != -1 && h->array[l] > h->array[i])
        max = l;
    else
        max = i;
    if(r != -1 && h->array[r] > h->array[max])
        max = r;
    if(max != i){
        temp = h->array[i];
        h->array[i] = h->array[max];
        h->array[max] = temp;
        PercolateDown(h, max);
    }
    else
        return;
}

int DeleteMax(struct Heap *h){ // root 값(최대값) 출력하며 노드 삭제 후 재정렬
    int data;
    if(h->count == 0)
        return -1;
    data = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, 0);
    return data;
}

void ResizeHeap(struct Heap *h){ // heap의 capacity 조정
    int *array_old = h->array;
    h->array = (int *) malloc(sizeof(int) * h->capacity * 2);
    if(h->array == NULL){
        printf("Memory Error");
        return;
    }
    for(int i = 0; i < h->capacity; i++){
        h->array[i] = array_old[i];
        h->capacity *= 2;
        free(array_old);
    }
}

void Insert(struct Heap *h, int data){ // heap에 항목 추가
    int i;
    if(h->count == h->capacity)
        ResizeHeap(h);
    if(h->count == 0){
        h->array[h->count++] = data;
        return;
    }
    h->count++;
    i = h->count - 1;
    while(i>=0 && data > h->array[(i - 1) / 2]){
        if(i == 0)
            break;
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = data;
}

void DestroyHeap(struct Heap *h){ // heap 삭제
    if(h == NULL)
        return;
    free(h->array);
    free(h);
}

int* Heapsort(int A[], int n){ // heap sorting, 책과 다름
    int* out = (int *) malloc(sizeof(int) * n);
    struct Heap *h = CreateHeap(n, "max");
    int temp;
    for(int i=0; i<n; i++)
        Insert(h, A[i]);
    for(int i=0; i<n; i++){
        temp = DeleteMax(h);
        out[i] = temp;
    }
    return out;
}

// problem 29
void Delete(struct Heap *h, int i){
    int key;
    if(h->count < i){
        printf("Wrong position");
        return;
    }
    key = h->array[i];
    h->array[i] = h->array[h->count-1];
    h->count--;
    PercolateDown(h, i);
}

int* FindMaxInWindow(int A[], int numA, int w){
    int next_remove, max, delete_index;
    int iter = numA - w + 1;
    struct Heap *h = CreateHeap(w, "max");
    int *B = (int *) malloc(sizeof(int) * (iter));

    for(int i=0; i<iter; i++){
        if(i == 0)
            for(int j=i; j<i+w; j++)
                Insert(h, A[j]);
        else
            Insert(h, A[i+w-1]);

        next_remove = A[i];
        B[i] = GetMaximum(h);

        // visualize heap element
        /*
        for(int z=0; z<h->count; z++){
            printf("%d ", h->array[z]);
            if(z == h->count - 1)
                printf("\n");
        }
        */

        for(int k=0; k<h->count; k++)
            if(next_remove == h->array[k]){
                delete_index = k;
                break;
            }
        Delete(h, delete_index);
    }
    return B;
}


int main() {
    int capacity = 100;
    char *heap_type = "max";
    struct Heap *h = NULL;

    int sample[15] = {10, 15, 24, 2, 5, 19, 1, 100, 59, 3, 33, 45, 98, 191, 200};
    int numSample = 15;

    int root_left, root_right;
    int any_child_left, any_child_right;
    int any_parent1, any_parent2;
    int out1, out2;
    int *out_heapsort;

    h = CreateHeap(capacity, heap_type);
    for(int i=0; i<numSample; i++)
        Insert(h, sample[i]);

    printf("---Current Heap state---\n");
    for(int i=0; i<h->count; i++){
        printf("%d ", h->array[i]);
        if(i == h->count - 1)
            printf("\n");
    }

    printf("Current Maximum value = %d\n", GetMaximum(h));

    root_left = h->array[LeftChild(h, 0)];
    root_right = h->array[RightChild(h, 0)];
    printf("Root's left child value = %d\n", root_left);
    printf("Root's right child value = %d\n", root_right);

    any_child_left = h->array[LeftChild(h, 1)];
    any_child_right = h->array[RightChild(h, 4)];
    printf("59's left child value = %d\n", any_child_left);
    printf("33's right child value = %d\n", any_child_right);

    any_parent1 = h->array[Parent(h, 3)];
    any_parent2 = h->array[Parent(h, 11)];
    printf("24's parent value = %d\n", any_parent1);
    printf("15's parent value = %d\n", any_parent2);

    out1 = DeleteMax(h);
    out2 = DeleteMax(h);
    printf("1st max value = %d\n", out1);
    printf("2nd max value = %d\n", out2);

    printf("---Current Heap state---\n");
    for(int i=0; i<h->count; i++){
        printf("%d ", h->array[i]);
        if(i == h->count - 1)
            printf("\n");
    }
    printf("Current Maximum value = %d\n", GetMaximum(h));

    out_heapsort = Heapsort(sample, numSample);
    for(int i=0; i<numSample; i++){
        printf("%d ", out_heapsort[i]);
        if(i == numSample - 1)
            printf("\n");
    }

    DestroyHeap(h);

    // problem 29
    int arr[8] = {1, 3, -1, -3, 5, 3, 6, 7};
    int arr2[8] = {2, 7, 10, 5, 3, 6, 9, 1};
    int numA = 8;
    int w = 4;
    int *out;

    out = FindMaxInWindow(arr, numA, w);
    printf("Problem29's Result\n");
    for(int i=0; i<numA-w+1; i++){
        printf("%d ", out[i]);
        if(i == numA - w)
            printf("\n");
    }

    out = FindMaxInWindow(arr2, numA, w);
    printf("Problem29's Result\n");
    for(int i=0; i<numA-w+1; i++){
        printf("%d ", out[i]);
        if(i == numA - w)
            printf("\n");
    }

    return 0;
}