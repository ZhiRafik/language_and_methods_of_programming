#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    float number;
    int base;
    int precision;

    int integerPart;
    float fractionalPart;

    char result[100];
    int index;

    int remainder;
    int i;

    // ввод данных
    printf("Введите число в десятичной системе: ");
    scanf("%f", &number);

    printf("Введите основание системы (2..9): ");
    scanf("%d", &base);

    printf("Введите количество знаков после запятой N: ");
    scanf("%d", &precision);

    // извлечение целой и дробной частей
    if (number < 0) {
        number = -number;
        result[0] = '-';
        index = 1;
    } else {
        index = 0;
    }

    integerPart = (int)number;
    fractionalPart = number - integerPart;

    // перевод целой части
    char temp[50];
    int tempIndex;
    tempIndex = 0;

    if (integerPart == 0) {
        temp[tempIndex] = '0';
        tempIndex = tempIndex + 1;
    }

    while (integerPart > 0) {
        remainder = integerPart % base;
        temp[tempIndex] = remainder + '0';
        tempIndex = tempIndex + 1;
        integerPart = integerPart / base;
    }

    // переворачиваем порядок
    for (i = tempIndex - 1; i >= 0; i--) {
        result[index] = temp[i];
        index = index + 1;
    }

    result[index] = '.';
    index = index + 1;

    // перевод дробной части
    for (i = 0; i < precision; i++) {
        fractionalPart = fractionalPart * base;
        remainder = (int) fractionalPart;
        result[index] = remainder + '0';
        index = index + 1;
        fractionalPart = fractionalPart - remainder;
    }

    result[index] = '\0';

    // вывод результата
    printf("Результат: %s\n", result);
    
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}