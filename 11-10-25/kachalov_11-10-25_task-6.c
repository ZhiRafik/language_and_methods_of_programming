#include <stdio.h>
#include <math.h>
#include <time.h>

// функция возвращает сумму собственных делителей числа x (без самого x)
long long sumProperDivisors(int x) {
    long long sum;
    int d;
    int q;
    int root;

    if (x <= 1) {
        return 0;
    }

    sum = 1; // 1 — собственный делитель для любого x > 1
    root = (int)sqrt((double)x);

    for (d = 2; d <= root; d++) {
        if (x % d == 0) {
            q = x / d;

            if (d == q) {
                sum = sum + d; // d — корень, добавляем один раз
            } else {
                sum = sum + d; // пара делителей d и q
                sum = sum + q;
            }
        }
    }

    return sum;
}

int main() {
    clock_t start = clock();

    int N;
    int i;
    int found;

    printf("Введите число N: \n");

    if (scanf("%d", &N) != 1) {
        return 0;
    }

    found = 0;

    for (i = 1; i <= N; i++) {
        long long s;
        s = sumProperDivisors(i);
        if (s == i) {
            printf("%d ", i);
            found = found + 1;
        }
    }

    if (found > 0) {
        printf("\n");
    } else {
        printf("Совершенных чисел в диапазоне 1..%d не найдено\n", N);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}