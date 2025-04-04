#include <stdlib.h>
#include <stdio.h>

int main() {
    // Вирівнювання, наприклад, 16 байтів
    size_t alignment = 16;
    // Розмір пам’яті, наприклад, 64 байти
    size_t size = 64;

    // Використовуємо aligned_alloc
    void* ptr = aligned_alloc(alignment, size);
    if (ptr == NULL) {
        perror("aligned_alloc failed");
        return 1;
    }

    printf("Memory allocated at address %p\n", ptr);

    // Не забудьте звільнити пам’ять
    free(ptr);

    return 0;
}
