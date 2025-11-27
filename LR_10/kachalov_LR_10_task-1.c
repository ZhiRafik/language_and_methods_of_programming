// LR_10_task1.c
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DELTA 3

// длина строки с учётом табуляции
size_t visual_len(const char *s) {
    size_t len = 0;
    while (*s && *s != '\n') {
        if (*s == '\t') {
            len += 4;
        } else {
            len++;
        }
        s++;
    }
    return len;
}

// выравнивание текста по правой границе
int main(void) {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        perror("output.txt");
        fclose(in);
        return 1;
    }

    char buf[4096];
    size_t max_len = 0;

    while (fgets(buf, sizeof(buf), in)) {
        size_t len = visual_len(buf);
        if (len > max_len) {
            max_len = len;
        }
    }

    size_t width = max_len + DELTA;
    rewind(in);

    while (fgets(buf, sizeof(buf), in)) {
        size_t len = visual_len(buf);
        size_t pad = width > len ? width - len : 0;

        for (size_t i = 0; i < pad; i++) {
            fputc(' ', out);
        }

        for (char *p = buf; *p && *p != '\n'; p++) {
            if (*p == '\t') {
                fputc(' ', out);
                fputc(' ', out);
                fputc(' ', out);
                fputc(' ', out);
            } else {
                fputc(*p, out);
            }
        }

        fputc('\n', out);
    }

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
