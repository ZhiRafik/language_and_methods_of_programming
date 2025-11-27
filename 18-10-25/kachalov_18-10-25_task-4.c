#include <stdio.h>  // стандартный ввод/вывод
#include <stdlib.h> // malloc, realloc, free
#include <string.h> // strlen, strcpy
#include <time.h>   // clock(), CLOCKS_PER_SEC

int main(void) {
    clock_t start = clock(); // начало измерения времени

    char filename[260];
    printf("Введите имя файла: ");
    if (scanf("%259s", filename) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r"); // открываем файл
    if (fp == NULL) {
        perror("Не удалось открыть файл");
        clock_t end_err = clock();
        double seconds_err = (double)(end_err - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds_err);
        return 1;
    }

    char *line_buf = NULL; // буфер текущей строки
    size_t line_len = 0; // текущая длина строки
    size_t line_cap = 0; // ёмкость буфера
    long line_count = 0; // количество строк

    char *max_line = NULL; // самая длинная строка
    size_t max_length = 0; // длина самой длинной строки

    int ch;
    while ((ch = fgetc(fp)) != EOF) { // читаем посимвольно
        if (line_len + 1 >= line_cap) { // увеличиваем буфер
            line_cap = line_cap ? line_cap * 2 : 64;
            line_buf = realloc(line_buf, line_cap);
        }
        line_buf[line_len++] = (char)ch;

        if (ch == '\n') { // конец строки
            line_buf[line_len] = '\0'; // завершаем строку
            line_count++;

            if (line_len > max_length) { // если строка длиннее предыдущей
                free(max_line);
                max_line = malloc(line_len + 1);
                strcpy(max_line, line_buf);
                max_length = line_len;
            }

            line_len = 0; // начинаем новую строку
        }
    }

    if (line_len > 0) { // если файл не заканчивается \n
        line_buf[line_len] = '\0';
        line_count++;
        if (line_len > max_length) {
            free(max_line);
            max_line = malloc(line_len + 1);
            strcpy(max_line, line_buf);
            max_length = line_len;
        }
    }

    if (line_count == 0) {
        printf("Файл пуст.\n");
    } else {
        printf("Количество строк: %ld\n", line_count);
        printf("Самая длинная строка (%zu символов):\n%s", max_length, max_line);
    }

    free(line_buf);
    free(max_line);
    fclose(fp);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения: %.6f секунд\n", seconds);
    return 0;
}