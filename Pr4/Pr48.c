#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t alignment = 16;
    size_t size = 64;

    // Використовуємо aligned_alloc
    void* ptr = aligned_alloc(alignment, size);
    if (ptr == NULL) {
        perror("aligned_alloc failed");
        return 1;
    }

    printf("Memory allocated at address %p\n", ptr);
    free(ptr);

    return 0;
}
