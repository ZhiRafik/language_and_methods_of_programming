#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 100

int main() {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.bin", "wb");
    char buf[1024], fixed[MAXLEN];
    int count = 0;

    if (!in || !out) {
        perror("fopen");
        return 1;
    }

    // считаем строки 
    while (fgets(buf, sizeof(buf), in)) count++;
    rewind(in);

    double n = count;
    fwrite(&n, sizeof(double), 1, out);

    // запись строк с заполнением пробелами 
    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }

        memset(fixed, ' ', MAXLEN);
        int to_copy = (int)len;
        if (to_copy > MAXLEN) to_copy = MAXLEN;
        memcpy(fixed, buf, to_copy);

        fwrite(fixed, sizeof(char), MAXLEN, out);
    }

    fclose(in);
    fclose(out);

    // чтение и вывод 
    FILE *f = fopen("output.bin", "rb");
    if (!f) {
        perror("output.bin");
        return 1;
    }

    double n_read;
    if (fread(&n_read, sizeof(double), 1, f) != 1) {
        fclose(f);
        return 1;
    }

    printf("Содержимое output.bin (задача 5), n = %.0f:\n", n_read);

    for (int i = 0; i < (int)n_read; i++) {
        if (fread(fixed, 1, MAXLEN, f) != MAXLEN) break;

        // убираем хвостовые пробелы по факту 
        int end = MAXLEN;
        while (end > 0 && fixed[end - 1] == ' ') end--;

        char tmp[MAXLEN + 1];
        memcpy(tmp, fixed, end);
        tmp[end] = '\0';

        printf("строка %d: \"%s\"\n", i + 1, tmp);
    }

    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
