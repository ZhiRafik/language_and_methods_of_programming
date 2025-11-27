#include <stdio.h>  // ввод/вывод
#include <time.h> // clock(), CLOCKS_PER_SEC

int main(void) {
    clock_t start = clock();

    char filename[260];
    printf("Введите имя входного файла: ");
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

    int ch;
    long line_num = 1; // номер строки
    int pos = 1;  // позиция символа в строке (с 1)
    long sum_even = 0; // сумма кодов символов на чётных позициях
    long sum_odd = 0; // сумма кодов символов на нечётных позициях

    while ((ch = fgetc(fp)) != EOF) { // читаем посимвольно
        if (ch == '\n') { // конец строки
            long diff = sum_even - sum_odd; // разность чётные - нечётные
            printf("Строка %ld: четные=%ld, нечетные=%ld, разность=%ld\n",
                   line_num, sum_even, sum_odd, diff);
            line_num++;
            pos = 1;
            sum_even = 0;
            sum_odd = 0;
        } else {
            if (pos % 2 == 0) {
                sum_even += ch; // чётная позиция
            } else sum_odd += ch; // нечётная позиция
            pos++;
        }
    }

    if (pos > 1) { // последняя строка без \n
        long diff = sum_even - sum_odd;
        printf("Строка %ld: четные=%ld, нечетные=%ld, разность=%ld\n",
               line_num, sum_even, sum_odd, diff);
    }

    fclose(fp);

    clock_t end = clock(); // конец замера
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    return 0;
}