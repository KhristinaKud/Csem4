#include <stdio.h>

void increase_stack() {
    int array1[1000];
    int array2[1000];
    int array3[1000];
    printf("Stack top inside function (array1): %p\n", (void*)&array1[0]);
    printf("Stack top inside function (array2): %p\n", (void*)&array2[0]);
    printf("Stack top inside function (array3): %p\n", (void*)&array3[0]);
}

int main() {
    increase_stack();
    return 0;
}