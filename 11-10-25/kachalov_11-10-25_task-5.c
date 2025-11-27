#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    int number;
    int a;
    int b;
    int c;
    int d;
    int count;
    int perLine;

    count = 0;
    perLine = 20;

    for (number = 1000; number <= 9999; number++) {
        a = number / 1000;
        b = (number / 100) % 10;
        c = (number / 10) % 10;
        d = number % 10;

        if (a != b) {
            if (a != c) {
                if (a != d) {
                    if (b != c) {
                        if (b != d) {
                            if (c != d) {
                                printf("%d ", number);
                                count = count + 1;

                                if (count % perLine == 0) {
                                    printf("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (count % perLine != 0) {
        printf("\n");
    }

    printf("Всего чисел: %d\n", count);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}