#include <stdio.h>
#include <time.h>

int main(void) {
    clock_t begin = clock();

    int n;
    printf("Введите n (n < 15): ");
    scanf("%d", &n);

    if (n < 1 || n >= 15) {
        printf("Ошибка: n должно быть от 1 до 14.\n");
        return 1;
    }

    int a[15][15] = {0};

    // первая строка
    a[0][0] = 1;

    // строим треугольник
    for (int i = 1; i < n; i++) {
        a[i][0] = 1;  // первый элемент в каждой строке — 1
        for (int j = 1; j <= i; j++) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    printf("Треугольник Паскаля:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }

    clock_t end = clock();
    double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}