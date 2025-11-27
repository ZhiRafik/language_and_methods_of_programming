#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Функция подсчёта слов
int count_words(const char *s) {
    int c = 0, in = 0;
    while (*s) {
        if (!isspace((unsigned char)*s) && !in) {
            in = 1;
            c++;
        } else if (isspace((unsigned char)*s)) {
            in = 0;
        }
        s++;
    }
    return c;
}

int main() {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    FILE *out = fopen("output.bin", "wb");
    if (!out) {
        perror("output.bin");
        fclose(in);
        return 1;
    }

    char buf[1024];

    // запись в бинарный файл
    while (fgets(buf, sizeof(buf), in)) {

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';    // убираем '\n'
        }

        float flen = (float)len;  // длина строки должна быть float!
        int words = count_words(buf);

        fwrite(&flen, sizeof(float), 1, out);  // пишем float длину
        fwrite(&words, sizeof(int), 1, out);   // пишем int количество слов
        fwrite(buf, sizeof(char), len, out);   // строка без '\n'
    }

    fclose(in);
    fclose(out);

    // --- чтение и вывод ---
    FILE *f = fopen("output.bin", "rb");
    if (!f) {
        perror("output.bin read");
        return 1;
    }

    printf("Содержимое output.bin (задание 4):\n\n");

    while (1) {
        float flen;
        int words;

        if (fread(&flen, sizeof(float), 1, f) != 1) break;
        if (fread(&words, sizeof(int), 1, f) != 1) break;

        int len = (int)flen;
        if (len < 0) len = 0;

        char *buff = malloc(len + 1);
        if (!buff) {
            perror("malloc");
            fclose(f);
            return 1;
        }

        if (fread(buff, 1, len, f) != (size_t)len) {
            free(buff);
            break;
        }

        buff[len] = '\0';

        printf("float_len = %.0f | words = %d | \"%s\"\n", flen, words, buff);

        free(buff);
    }

    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения: %.6f секунд\n", seconds);

    return 0;
}
