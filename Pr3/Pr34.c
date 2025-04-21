#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CPU_TIME 2

// Функція для генерації унікальних чисел у діапазоні
void generate_numbers(int *num, int count, int max_range) {
    for (int i = 0; i < count; i++) {
        num[i] = rand() % max_range + 1;
        for (int j = 0; j < i; j++) {
            if (num[i] == num[j]) {
                i--;
                break;
            }
        }
    }
}

// Функція для друку масиву чисел
void print_numbers(const char *label, int *num, int count) {
    printf("%s: ", label);
    for (int i = 0; i < count; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
}

int main() {
    int lottery1[7], lottery2[6];
    time_t start_time, current_time;
    double elapsed_time;

    srand(time(NULL));  // Ініціалізація генератора випадкових чисел

    start_time = time(NULL);

    while (1) {
        current_time = time(NULL);
        elapsed_time = difftime(current_time, start_time);

        if (elapsed_time >= MAX_CPU_TIME) {
            // Оброблення перевищення ліміту ресурсу
            printf("CPU time limit exceeded (%d seconds). No further generation possible.\n", MAX_CPU_TIME);
            break;
        }

        // Генерація чисел для обох лотерей
        generate_numbers(lottery1, 7, 49);  // 7 чисел із діапазону 1-49
        generate_numbers(lottery2, 6, 36);  // 6 чисел із діапазону 1-36

        // Виведення результатів
        print_numbers("Lottery numbers (1-49)", lottery1, 7);
        print_numbers("Lottery numbers (1-36)", lottery2, 6);

        printf("\n");
        sleep(1);  // Затримка для ітерації
    }

    return 0;
}
