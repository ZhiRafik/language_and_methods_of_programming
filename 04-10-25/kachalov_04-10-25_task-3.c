#include <stdio.h>
#include <time.h>

int getDigitsNumber(unsigned n) {
    unsigned digits = (n == 0) ? 1u : 0u;
    while (n > 0) {
        n >>= 1;
        digits++;
    }
    return digits;
}

int main(void) {
    clock_t start = clock();

    unsigned n;
    printf("Введите n: ");
    scanf("%u", &n);

    unsigned res = 1u;
    int digitsNumber = getDigitsNumber(n);
    for (int i = 0; i < digitsNumber; i++) {
        res <<= 1; // сдвигаем, чтобы освободить место для следующего бита
        if ((n & 1u) == 0) {
            res |= 1u; // если бит 0 — ставим 1
        }
        n >>= 1;
    }
    res <<= 1;
    res++;
    printf("Результирующее число после инвертирования и добавления единиц: %u\n", res);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}