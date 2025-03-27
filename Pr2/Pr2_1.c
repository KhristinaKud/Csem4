#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    //максимальне значення часу
    time_t max_32bit = INT_MAX;
    time_t max_64bit = LLONG_MAX;

    //виведення Для 32-ї системи
    printf("Maximum time for 32-bit time_t: %ld seconds\n", max_32bit);
    printf("End date (32-bit): %s", ctime(&max_32bit));

    //виведення Для 64-ї системи
    printf("Maximum time for 64-bit time_t: %lld seconds\n", max_64bit);
    printf("End date (64-bit): %s", ctime(&max_64bit));

    return 0;
}