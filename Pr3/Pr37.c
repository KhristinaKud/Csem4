#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1024;
    int count = 0;
    while (1) {
        char* ptr = malloc(size);
        if (ptr == NULL) {
            printf("Memory allocation failed at block %d (approx %lu MB allocated)\n", count, count);
            break;
        }
        count++;
    }
    return 0;
}