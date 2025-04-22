#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t block_size = 1024 * 1024; // 1 MB
    int count = 0;
    while (1) {
        char* ptr = malloc(block_size);
        if (ptr == NULL) {
            printf("Memory allocation failed at block %d (approx %lu MB allocated)\n", count, count);
            break;
        }
        count++;
        printf("Allocated %d MB\n", count);
    }
    return 0;
}
