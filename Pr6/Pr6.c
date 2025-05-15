#include <stdio.h>
#include <stdlib.h>

int *get_ptr() {
    int *x = malloc(sizeof(int));
    *x = 5;
    return x;
}

int main() {
    int *ptr = get_ptr();
    printf("%d", *ptr);
    free(ptr); // Важливо!
    return 0;
}