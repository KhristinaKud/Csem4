#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    // Установлюємо максимальне значення для time_t
    time_t max_time =LONG_MAX; // LONG_MAX підходить для time_t як ціле число
    //  макс значення
    printf("Max value time_t: %lld\n", (long long)max_time);
    // Відображення часу у форматі
    struct tm *max_time_tm = gmtime(&max_time);
    if (max_time_tm) {
        printf("Time? when time_t finished: %s", asctime(max_time_tm));
    } else {
        printf("Error.\n");
    }

    return 0;
}
