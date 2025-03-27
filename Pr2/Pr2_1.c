#include <stdio.h>
#include <time.h>
#include <limits.h>

// Основна функція
int main() {
    // Оголошення змінної для зберігання максимального значення time_t
    time_t max_time;

    // Визначення максимального значення time_t залежно від архітектури
#if (INT_MAX == 2147483647) // 32-бітний time_t
    max_time = (time_t)INT_MAX;
#else // 64-бітний time_t
    max_time = (time_t)LLONG_MAX;
#endif

    // Конвертація максимального значення time_t у структуру часу
    struct tm *tm_info = localtime(&max_time);
    if (tm_info) { // Якщо конвертація успішна
        printf("Maximum representable time: %s", asctime(tm_info)); // Виведення дати
    }
    else { // Якщо конвертація не вдалася
        printf("Time conversion failed, value might be too large\n");
    }

    return 0; // Повернення нуля для успішного завершення програми
}
