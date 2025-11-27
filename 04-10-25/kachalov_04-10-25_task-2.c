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
    unsigned m;
    printf("Введите n и m: ");
    scanf("%u %u", &n, &m);
    int diff = getDigitsNumber(n) - m;
    if (diff < 0) {
        n <<= (-diff);
    }

    unsigned tn = n;
    int temp = 0;
    for (int i = 0; i < m; i++) { // последние m
        temp += tn % 2;
        tn >>= 1;
    }
    printf("Сумма первых m цифр n в двоичной записи: %i\n", temp);

    tn = n;
    temp = 0;
    tn >>= (getDigitsNumber(tn) - m); // оставили только первые m
    for (int i = 0; i < m; i++) { // первые m
        temp += tn % 2;
        tn >>= 1;
    }
    printf("Сумма последних m цифр n в двоичной записи: %i\n", temp);

    int sum = 0;
    int sign = 1;  // начинаем с плюса
    tn = n;
    while (tn > 0) {
        sum += sign * (tn % 2);
        sign = -sign; // меняем знак
        tn >>= 1;
    }
    printf("Знакочередующаяся сумма цифр n в двоичной записи: %i\n", sum);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}