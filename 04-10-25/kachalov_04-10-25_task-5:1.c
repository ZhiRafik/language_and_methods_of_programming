#include <stdio.h>
#include <time.h>

int main(void) {
    clock_t start = clock();
/*
0 - 1
1 - 1
5 - 3
16 - 5
255 - 8
*/
    unsigned n;
    unsigned nt;
    printf("Введите n: ");
    scanf("%u", &n);
    nt = n;
    unsigned digits = (n == 0) ? 1u : 0u;
    while (nt > 0) {
        nt >>= 1;
        digits++;
    }
    printf("Количество цифр в двоичной записи: %u\n", digits);
/*
Первая цифра всегда 1, либо число равно 0. 
Последняя цифра определяется кратностью двойки
*/
    if (digits == 1) {
        printf("Число длиной 1 -> после замены первой и последней цифры ничего не меняется\n");
        printf("Число после замены: %u\n", n);
    } else if (n % 2 == 1) {
        printf("Первая и последняя цифра двоичной записи равны единице -> ничего не меняется\n");
        printf("Число после замены: %u\n", n);
    } else { 
        printf("Первая цифра 1 (всегда для >0), вторая здесь 0 -> делаем замену\n");
        n -= (1ULL << (digits-1));
        n++;
        printf("Число после замены: %u\n", n);
    }
        
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}