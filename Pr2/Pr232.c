#include <stdio.h>
#include <stdlib.h>


int data = 10;
int bss;

void text_segment() {
    printf("Function address (text segment): %p\n", text_segment);
}
int main() {
    int stack;
    int *heap = malloc(sizeof(int));
    text_segment();
    printf("data segment: %p\n", &data);
    printf("bss segment: %p\n", &bss);
    printf("Heap allocation: %p\n", heap);
    printf("Stack allocation: %p\n", &stack);
    free(heap);


    return 0;
}