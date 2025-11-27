#include <stdio.h>
#include <time.h>

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(void) {
    clock_t start = clock();

    int numbers[120];
    int count = 0;
    int n = 1;

    // находим первые 120 чисел с суммой цифр = 10
    while (count < 120) {
        if (sumOfDigits(n) == 10) {
            numbers[count++] = n;
        }
        n++;
    }

    // вывод в виде матрицы 10x12
    printf("Первые 120 натуральных чисел, сумма цифр которых равна 10:\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%5d", numbers[i * 12 + j]);
        }
        printf("\n");
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}