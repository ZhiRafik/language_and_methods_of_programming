#include <stdio.h>
#include <time.h>

int isLeap(int year) {
    // проверка високосного года
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

int daysInMonth(int month, int year) {
    // количество дней в месяце
    if (month == 2) {
        if (isLeap(year)) {
            return 29;
        } else {
            return 28;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

long dateToDays(int day, int month, int year) {
    // перевод даты в количество дней от условного нулевого года
    long days; // вдруг много
    int i;

    days = day;

    for (i = 1; i < month; i++) {
        days = days + daysInMonth(i, year);
    }

    for (i = 1; i < year; i++) {
        days = days + 365;
        if (isLeap(i)) {
            days = days + 1;
        }
    }

    return days;
}

int main() {
    clock_t start = clock();

    int d1;
    int m1;
    int y1;

    int d2;
    int m2;
    int y2;

    long days1;
    long days2;
    long result;

    // ввод двух дат
    printf("Введите первую дату (день месяц год): ");
    scanf("%d %d %d", &d1, &m1, &y1);

    printf("Введите вторую дату (день месяц год): ");
    scanf("%d %d %d", &d2, &m2, &y2);

    days1 = dateToDays(d1, m1, y1);
    days2 = dateToDays(d2, m2, y2);

    // модуль разницы
    if (days1 > days2) {
        result = days1 - days2;
    } else {
        result = days2 - days1;
    }

    printf("Количество дней между датами: %ld\n", result);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}