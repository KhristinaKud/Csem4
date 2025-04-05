#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int x;
};

int main() {
    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        printf("calloc failed\n");
        return 1;
    } else {
        printf("Allocated memory at %p\n", ptr);
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        printf("reallocarray failed\n");
        free(ptr); // Звільняємо пам'ять, якщо reallocarray повертає NULL
        return 1;
    } else {
        printf("Reallocated with reallocarray to %p\n", newptr);
    }
    free(newptr);
    return 0;
}
