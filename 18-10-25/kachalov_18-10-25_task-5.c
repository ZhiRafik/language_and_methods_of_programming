#include <stdio.h>  // стандартный ввод/вывод
#include <stdlib.h> // malloc, realloc, free
#include <string.h> // strlen, strcpy
#include <time.h>   // clock(), CLOCKS_PER_SEC

int main(void) {
    clock_t start = clock(); // начало измерения времени

    char input_name[260];
    char output_name[260];
    printf("Введите имя входного файла: ");
    if (scanf("%259s", input_name) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    printf("Введите имя выходного файла: ");
    if (scanf("%259s", output_name) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    FILE *in = fopen(input_name, "r"); // открываем входной файл
    if (in == NULL) {
        perror("Не удалось открыть входной файл");
        clock_t end_err = clock();
        double seconds_err = (double)(end_err - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds_err);
        return 1;
    }

    FILE *out = fopen(output_name, "w"); // создаём выходной файл
    if (out == NULL) {
        perror("Не удалось создать выходной файл");
        fclose(in);
        clock_t end_err = clock();
        double seconds_err = (double)(end_err - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds_err);
        return 1;
    }

    char *line_buf = NULL; // буфер для строки
    size_t line_len = 0;   // длина текущей строки
    size_t line_cap = 0;   // ёмкость буфера
    int ch;
    int found_dot = 0;     // флаг: встречена ли точка

    while ((ch = fgetc(in)) != EOF) { // читаем файл посимвольно
        if (line_len + 1 >= line_cap) { // увеличиваем буфер при необходимости
            line_cap = line_cap ? line_cap * 2 : 64;
            line_buf = realloc(line_buf, line_cap);
        }

        line_buf[line_len++] = (char)ch;

        if (ch == '.') {
            found_dot = 1; // если встретили точку — дальше не записываем
        }
        if (ch == '\n') { // конец строки
            line_buf[line_len] = '\0'; // завершаем строку

            if (found_dot) { // если была точка — обрезаем
                for (size_t i = 0; i < line_len; i++) {
                    if (line_buf[i] == '.') { // нашли первую точку
                        line_buf[i + 1] = '\0'; // обрезаем строку после неё
                        break;
                    }
                }
            }

            fputs(line_buf, out); // записываем строку в выходной файл
            // fputs() копирует символы только до '\0'
            line_len = 0; // начинаем новую строку
            found_dot = 0; // сбрасываем флаг
        }
    }

    if (line_len > 0) { // последняя строка без '\n'
        line_buf[line_len] = '\0';
        if (found_dot) {
            for (size_t i = 0; i < line_len; i++) {
                if (line_buf[i] == '.') {
                    line_buf[i + 1] = '\0';
                    break;
                }
            }
        }
        fputs(line_buf, out);
    }

    free(line_buf);
    fclose(in);
    fclose(out);

    printf("Выходной файл успешно создан: %s\n", output_name);

    clock_t end = clock(); // конец измерения времени
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}