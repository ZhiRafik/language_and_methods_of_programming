#include <stdio.h>
#include <time.h>

int isPrime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    clock_t begin = clock();

    printf("Четвёрки простых чисел в пределах одного десятка:\n");

    for (int start = 0; start < 100; start += 10) {
        int count = 0;
        int primes[10];

        for (int n = start + 1; n <= start + 10 && n <= 100; n++) {
            if (isPrime(n)) {
                primes[count++] = n;
            }
        }

        if (count >= 4) {
            printf("[%i-%i]: ", (start + 1), (start + 10));
            for (int i = 0; i < count; i++) {
                printf("%i ", primes[i]);
            }
            printf("\n");
        }
    }

    clock_t end = clock();
    double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}