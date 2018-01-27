#include <stdio.h>

int main(void) {
    printf("Current line: %d \n", __LINE__);
    printf("Current system time: %s \n", __TIME__);
    printf("Current file path: %s \n", __FILE__);
    
    #ifdef __cplusplus
        printf("Current compiler is C++ \n");
    #else
        printf("Current compiler is C \n");
    #endif
    
    return 0;
}
