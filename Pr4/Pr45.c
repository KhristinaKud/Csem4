#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(100);
    if (!ptr) {
        perror("malloc failed");
        return 1;
    } else {
        printf("malloc: %p\n", ptr);
    }

    void *new_ptr = realloc(ptr, (size_t)-1);
    if (!new_ptr) {
        printf("Original pointer still valid at %p\n", ptr);
        free(ptr);
    } else {
        ptr = new_ptr;
        free(ptr);
    }

    return 0;
}
