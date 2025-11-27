#include <stdio.h>
#include <stdlib.h> // malloc, realloc, free
#include <string.h> // strlen
#include <ctype.h> // isalpha
#include <time.h> // clock(), CLOCKS_PER_SEC

// проверка: является ли символ частью слова
int is_word_char(int ch) {
    return isalpha((unsigned char)ch) || ch == '-' || ch == '\''; // допускаем буквы, дефис и апостроф
}

int main(void) {
    clock_t start = clock();

    char filename[260];
    printf("Введите имя файла: ");
    if (scanf("%259s", filename) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL) {
        perror("Не удалось открыть файл");
        clock_t end_err = clock();
        double seconds_err = (double)(end_err - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds_err);
        return 1;
    }

    int *length_count = NULL; // динамический массив частот по длинам слов
    size_t count_size = 0; // текущая длина массива
    char *word_buf = NULL; // временный буфер
    size_t buf_size = 0, buf_cap = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (is_word_char(ch)) { // если буква
            if (buf_size + 1 >= buf_cap) {
                buf_cap = buf_cap ? buf_cap * 2 : 16; // увеличиваем буфер
                word_buf = realloc(word_buf, buf_cap);
            }
            word_buf[buf_size++] = (char)ch; // добавляем символ (fgetc(fp) возвращает значение типа int, не char)
        } else { // конец слова
            if (buf_size > 0) {
                word_buf[buf_size] = '\0'; // завершаем строку
                int len = (int)strlen(word_buf); // длина слова

                if (len >= (int)count_size) { // увеличиваем массив под новую длину
                    length_count = realloc(length_count, (len + 1) * sizeof(int));
                    for (size_t i = count_size; i <= (size_t)len; i++) length_count[i] = 0;
                    count_size = len + 1;
                }

                length_count[len]++; // увеличиваем счётчик слов этой длины
                buf_size = 0; // сбрасываем буфер
            }
        }
    }

    if (buf_size > 0) { // если файл закончился на слове
        word_buf[buf_size] = '\0';
        int len = (int)strlen(word_buf);
        if (len >= (int)count_size) {
            length_count = realloc(length_count, (len + 1) * sizeof(int));
            for (size_t i = count_size; i <= (size_t)len; i++) length_count[i] = 0;
            count_size = len + 1;
        }
        length_count[len]++;
    }

    free(word_buf);
    fclose(fp);

    if (count_size == 0) {
        printf("Файл не содержит слов.\n");
    } else {
        printf("Количество слов по длинам:\n");
        for (size_t i = 1; i < count_size; i++) {
            if (length_count[i] > 0)
                printf("Длина %zu: %d слов(а)\n", i, length_count[i]);
        }
    }

    free(length_count);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}