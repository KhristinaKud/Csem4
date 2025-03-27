#include <stdio.h>
#include <stdlib.h>

//  .data
int global_data = 42;

//  .bss
int global_bss;

void sample_function() {
    printf("This is a function in .text\n");
}

int main() {
    // Локальна змінна на стеку
    int stack_var;

    // Змінна на купі (heap)
    int *heap_var = malloc(sizeof(int));
    *heap_var = 10;

    // Виведення адрес
    printf("Stack top (stack_var) is near: %p\n", &stack_var);
    printf("Global initialized (data segment): %p\n", &global_data);
    printf("Global uninitialized (bss segment): %p\n", &global_bss);
    printf("Function (text segment): %p\n", sample_function);
    printf("Heap variable: %p\n", heap_var);

    // Звільнення пам’яті
    free(heap_var);

    return 0;
}