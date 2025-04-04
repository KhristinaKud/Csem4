#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr1 = realloc(NULL, 6); //  malloc(6)
    printf("ptr 1return: %p\n", ptr1);
    void *ptr2 = realloc(ptr1, 0);   //  free(ptr1)
    printf("ptr2 return: %p\n", ptr2);
    return 0;
}