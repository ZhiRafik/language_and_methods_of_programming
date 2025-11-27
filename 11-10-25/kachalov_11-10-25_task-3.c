#include <stdio.h>
#include <time.h>

// вычисляеv день недели по формуле Зеллера
// возвращает 0 - суббота, 1 - воскресенье, 2 - понедельник, ..., 6 - пятница
int dayOfWeek(int day, int month, int year) {
    int q;
    int m;
    int K;
    int J;
    int h;

    q = day;

    if (month == 1) {
        month = 13;
        year = year - 1;
    }

    if (month == 2) {
        month = 14;
        year = year - 1;
    }

    m = month;
    K = year % 100;
    J = year / 100;

    h = (q + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;

    return h;
}

int main() {
    clock_t start = clock();

    int year;
    int dow;
    int blackFridays;

    blackFridays = 0;

    for (year = 2001; year <= 2100; year++) {
        int month;

        for (month = 1; month <= 12; month++) {
            dow = dayOfWeek(13, month, year);

            // в формуле Зеллера пятница = 6
            if (dow == 6) {
                blackFridays = blackFridays + 1;
            }
        }
    }

    printf("Количество чёрных пятниц в XXI веке: %d\n", blackFridays);
    
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    
    return 0;
}