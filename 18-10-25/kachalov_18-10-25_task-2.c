#include <stdio.h>  // стандартный ввод/вывод
#include <ctype.h>  // isalpha, isdigit, tolower
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

    int letters[26] = {0}; // счётчик букв a-z
    int digits[10] = {0};  // счётчик цифр 0-9
    int total_letters = 0; // общее количество букв
    int total_digits = 0;  // общее количество цифр
    int lines = 0;         // количество строк в файле

    int ch;
    while ((ch = fgetc(fp)) != EOF) { // читаем посимвольно
        if (isalpha((unsigned char)ch)) { // если буква
            ch = tolower(ch); // приводим к нижнему регистру
            letters[ch - 'a']++; // увеличиваем счётчик
            total_letters++;
        } else if (isdigit((unsigned char)ch)) { // если цифра
            digits[ch - '0']++;
            total_digits++;
        }
        if (ch == '\n') lines++; // считаем строки
    }

    if (lines == 0) lines = 1; // если файл без \n, считаем 1 строку

    printf("\nКоличество каждой буквы:\n");
    for (int i = 0; i < 26; i++) {
        if (letters[i] > 0) printf("%c : %d\n", 'a' + i, letters[i]);
    }

    printf("\nКоличество каждой цифры:\n");
    for (int i = 0; i < 10; i++) {
        if (digits[i] > 0) printf("%d : %d\n", i, digits[i]);
    }

    double avg_letters = (double)total_letters / lines; // среднее букв на строку
    double avg_digits = (double)total_digits / lines;   // среднее цифр на строку

    printf("\nОбщее количество букв: %d\n", total_letters);
    printf("Общее количество цифр: %d\n", total_digits);
    printf("Количество строк: %d\n", lines);
    printf("Среднее количество букв в строке: %.2f\n", avg_letters);
    printf("Среднее количество цифр в строке: %.2f\n", avg_digits);

    fclose(fp); // закрываем файл

    clock_t end = clock(); // конец измерения времени
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}