#include <stdio.h>
int global_array[1000] = {1};
int main() {
    int local_array[1000];          // Неініціалізований локальний масив
    int local_array_init[1000] = {1}; // Ініціалізований локальний масив
    printf("Hello, World!\n");
    return 0;
}