#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start = clock();

    // Открываем входной файл для чтения
    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    char buf[1024];
    size_t maxLen = 0;

    // Первый проход: ищем максимальную длину строки (без '\n')
    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            len--;  // не считаем символ перевода строки
        }
        if (len > maxLen) {
            maxLen = len;
        }
    }

    if (maxLen == 0) {
        fclose(in);
        printf("Файл пустой.\n");
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds);
        return 0;
    }

    // Буфер фиксированной длины = максимальной длине строки
    char *fixed = malloc(maxLen);
    if (!fixed) {
        perror("malloc fixed");
        fclose(in);
        return 1;
    }

    // Второй проход: записываем в бинарный файл
    rewind(in);
    FILE *out = fopen("output.bin", "wb");
    if (!out) {
        perror("output.bin");
        free(fixed);
        fclose(in);
        return 1;
    }

    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }

        int len_int = (int) len;  // реальная длина строки
        fwrite(&len_int, sizeof(int), 1, out);  // записываем int

        // Заполняем фиксированный массив нулями и копируем строку
        memset(fixed, 0, maxLen);
        if (len > maxLen) len = maxLen;  // защита от переполнения
        memcpy(fixed, buf, len);

        // Записываем весь массив char фиксированной длины
        fwrite(fixed, 1, maxLen, out);
    }

    fclose(in);
    fclose(out);

    // Теперь читаем output.bin и выводим содержимое для проверки
    FILE *f = fopen("output.bin", "rb");
    if (!f) {
        perror("output.bin read");
        free(fixed);
        return 1;
    }

    printf("Содержимое output.bin (задача 2):\n");
    printf("Фиксированная длина массива char = %zu байт\n\n", maxLen);

    while (1) {
        int len_int;
        if (fread(&len_int, sizeof(int), 1, f) != 1) break;

        if (fread(fixed, 1, maxLen, f) != maxLen) break;

        if (len_int < 0) len_int = 0;
        if ((size_t)len_int > maxLen) len_int = (int)maxLen;

        char *tmp = malloc(len_int + 1);
        if (!tmp) {
            perror("malloc tmp");
            break;
        }

        memcpy(tmp, fixed, len_int);
        tmp[len_int] = '\0';

        // len_int — логическая длина строки,
        // maxLen — реальная длина массива char в файле (фиксированная)
        printf("len = %d (логич.), buffer = %zu (фикс.) | \"%s\"\n",
               len_int, maxLen, tmp);

        free(tmp);
    }

    fclose(f);
    free(fixed);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения: %.6f секунд\n", seconds);

    return 0;
}