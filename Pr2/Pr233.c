#include <stdio.h>

void increase_stack() {
    int array1[1000];
    int array2[1000];
    printf("Stack top inside function (array1): %p\n", &array1);
    printf("Stack top inside function (array2): %p\n", &array2);

}

int main() {
    int a;
    printf("Initial stack top: %p\n", &a);
    increase_stack();
    return 0;
}