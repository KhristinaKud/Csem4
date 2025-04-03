#include <stdio.h>
#include <stdlib.h>

int data = 5;
int bss;

int main() {
    int stack;
    // Змінна на купі (heap)
    int *heap = malloc(sizeof(int));
    // Виведення адрес
    printf ("Text segment : %p\n", (void*)main());
    printf ("Initialized data segmant: %p\n", (void*)&data);
    printf ("BSS segmant: %p\n", (void*)&bss);
    printf ("Heap segment: %p\n", (void*)heap);
    printf ("Stack segment: %p\n", (void*) &stack);

    // Звільнення пам’яті
    free(heap);

    return 0;
}