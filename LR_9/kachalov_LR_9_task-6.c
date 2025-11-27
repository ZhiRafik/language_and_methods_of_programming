#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Функция для подсчёта суммы кодов символов строки
int sum_codes(const unsigned char *s) {
    int sum = 0;
    while (*s) {
        sum += *s;
        s++;
    }
    return sum;
}

int main() {
    clock_t start = clock();

    // Открываем входной текстовый файл
    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    // Открываем бинарный файл для записи
    FILE *out = fopen("output.bin", "wb");
    if (!out) {
        perror("output.bin");
        fclose(in);
        return 1;
    }

    char buf[1024];

    // Запись в бинарный файл по формату:
    // int длина, int сумма_кодов, char[длина] строка без '\n'
    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';  // убираем '\n'
        }

        int len_int = (int)len; // длина строки
        int sum = sum_codes((unsigned char*)buf);  // сумма кодов символов

        fwrite(&len_int, sizeof(int), 1, out);   // пишем длину
        fwrite(&sum, sizeof(int), 1, out);   // пишем сумму кодов
        fwrite(buf, sizeof(char), len, out);  // пишем саму строку
    }

    fclose(in);
    fclose(out);

    // Теперь читаем бинарный файл и выводим его содержимое
    FILE *f = fopen("output.bin", "rb");
    if (!f) {
        perror("output.bin read");
        return 1;
    }

    printf("Содержимое output.bin (задание 6):\n\n");

    while (1) {
        int len_int;
        int sum;

        // Читаем длину
        if (fread(&len_int, sizeof(int), 1, f) != 1) break;
        // Читаем сумму кодов
        if (fread(&sum, sizeof(int), 1, f) != 1) break;

        if (len_int < 0) len_int = 0;

        char *buff = malloc(len_int + 1);
        if (!buff) {
            perror("malloc");
            fclose(f);
            return 1;
        }

        // Читаем строку указанной длины
        if (fread(buff, 1, len_int, f) != (size_t)len_int) {
            free(buff);
            break;
        }
        buff[len_int] = '\0';

        printf("len = %d, sum_codes = %d | \"%s\"\n", len_int, sum, buff);

        free(buff);
    }

    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения: %.6f секунд\n", seconds);

    return 0;
}
