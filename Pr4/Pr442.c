#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    while (i < 2) {
        if (!ptr)
            ptr = malloc(16);
        printf("ptr = %p\n", ptr);
        strcpy(ptr, "mam");
        printf("Value before free: %s\n", (char*)ptr);
        free(ptr);
        ptr = NULL; // Виправлення
        i++;
    }
    return 0;
}