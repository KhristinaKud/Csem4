#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 12345678

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int sorted(const int *array, int size) {
    for (int i = 1; i < size; ++i) {
        if (array[i - 1] > array[i]) {
            return 0;
        }
    }
    return 1;
}
void generate_sorted(int *array,  int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
}
void generate_reverse_sorted(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = (int)(size - i);
    }
}
void generate_random(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }
}
void test_sort(const char *name, void (*generator)(int *, int)) {
    int *array = malloc(SIZE * sizeof(int));
    generator(array, SIZE);
    clock_t st = clock();
    qsort(array, SIZE, sizeof(int), compare);
    clock_t end = clock();
    double time = (double)(end - st) / CLOCKS_PER_SEC;
    printf("Test: %s\n", name);
    printf("  Time of sorting: %.5f \n", time);
    printf("  Sorting is corect: %s\n\n", sorted(array, SIZE) ? "yes" : "no");
    free(array);
}

int main() {
    srand(time(NULL));
    test_sort("Sorted: ", generate_sorted);
    test_sort("Reverse sorted: ", generate_reverse_sorted);
    test_sort("Random: ", generate_random);

    return 0;
}