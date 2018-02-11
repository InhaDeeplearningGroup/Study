#include <stdio.h>
#include <stdlib.h>

void main() {
    int *ar, size, i;

    size = 5;
    ar = (int *)malloc(size*sizeof(int));
    for(i = 0; i < size; ++i)
        ar[i] = i;
    for(i = 0; i < size; ++i)
        printf("%d", ar[i]);
        printf("\n");

    size = 10;
    ar = (int *)realloc(ar, size*sizeof(int));
    for(i = 5; i < size; ++i)
        ar[i] = i;
    for(i = 0; i < size; ++i)
        printf("%d", ar[i]);
        printf("\n");

    free(ar);
}
