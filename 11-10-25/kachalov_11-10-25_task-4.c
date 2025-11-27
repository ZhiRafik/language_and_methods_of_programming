#include <stdio.h>
#include <math.h>
#include <time.h>

// сумма собственных делителей числа x (без самого x)
long long sumProperDivisors(int x) {
    long long sum;
    int d;
    int r;
    int root;

    if (x <= 1) {
        return 0;
    }

    sum = 1; // 1 всегда собственный делитель для x > 1
    root = (int)sqrt((double)x);

    for (d = 2; d <= root; d++) {
        if (x % d == 0) {
            r = x / d;

            if (d == r) {
                sum = sum + d; // квадрат: добавляем один раз
            } else {
                sum = sum + d;
                sum = sum + r;
            }
        }
    }

    return sum;
}

int main() {
    clock_t start = clock();

    int N;
    int i;

    int bestNumber;
    long long bestSum;
    
    printf("Введите N: \n");

    if (scanf("%d", &N) != 1) {
        return 0;
    }

    bestNumber = 1;
    bestSum = 0;

    for (i = 1; i <= N; i++) {
        long long s;

        s = sumProperDivisors(i);

        if (s > bestSum) {
            bestSum = s;
            bestNumber = i;
        } else {
            if (s == bestSum) {
                if (i < bestNumber) {
                    bestNumber = i;
                }
            }
        }
    }

    printf("%d %lld\n", bestNumber, bestSum);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}