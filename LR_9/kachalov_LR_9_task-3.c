#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.bin", "wb");
    char buf[1024];
    int count = 0;

    if (!in || !out) {
        perror("fopen");
        return 1;
    }

    // сначала считаем строки
    while (fgets(buf, sizeof(buf), in)) count++;
    rewind(in);

    double n = count;
    fwrite(&n, sizeof(double), 1, out);

    // запись строк с '\0' 
    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }
        fwrite(buf, sizeof(char), len + 1, out); // вместе с '\0'
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

    int lines = (int)n_read;
    printf("Содержимое output.bin (задача 3), n = %.0f:\n", n_read);

    for (int i = 0; i < lines; i++) {
        // читаем посимвольно до '\0'
        size_t cap = 128;
        size_t len = 0;
        char *s = malloc(cap);
        if (!s) {
            fclose(f);
            return 1;
        }

        while (1) {
            int c = fgetc(f);
            if (c == EOF) {
                s[len] = '\0';
                break;
            }
            if (len + 1 >= cap) {
                cap *= 2;
                char *tmp = realloc(s, cap);
                if (!tmp) {
                    free(s);
                    fclose(f);
                    return 1;
                }
                s = tmp;
            }
            s[len++] = (char)c;
            if (c == '\0') break;
        }

        printf("строка %d: \"%s\"\n", i + 1, s);
        free(s);
    }

    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
