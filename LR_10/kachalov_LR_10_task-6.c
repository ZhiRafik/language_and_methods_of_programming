// LR_10_task6.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

// разворачивание строки: табуляция -> 4 пробела
void expand_line(const char *src, char *dst, size_t dst_size) {
    size_t j = 0;
    for (size_t i = 0; src[i] && src[i] != '\n'; i++) {
        if (src[i] == '\t') {
            for (int k = 0; k < 4 && j + 1 < dst_size; k++) {
                dst[j++] = ' ';
            }
        } else {
            if (j + 1 < dst_size) {
                dst[j++] = src[i];
            }
        }
    }
    dst[j] = '\0';
}

// выравнивание строк по ширине
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

    if (max_len == 0) {
        fclose(in);
        fclose(out);
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Время выполнения: %.6f секунд\n", seconds);
        return 0;
    }

    size_t target = max_len;
    rewind(in);

    char line[8192];

    while (fgets(buf, sizeof(buf), in)) {
        expand_line(buf, line, sizeof(line));

        char *p = line;
        while (*p == ' ') {
            p++;
        }

        size_t len = strlen(p);
        while (len > 0 && p[len - 1] == ' ') {
            p[--len] = '\0';
        }

        if (len == 0) {
            fputc('\n', out);
            continue;
        }

        char *words[512];
        int wlen[512];
        int count = 0;
        int sum_len = 0;

        char *cur = p;
        while (*cur) {
            while (*cur == ' ') {
                cur++;
            }
            if (!*cur) {
                break;
            }

            words[count] = cur;
            int wl = 0;
            while (*cur && *cur != ' ') {
                cur++;
                wl++;
            }
            sum_len += wl;
            wlen[count] = wl;
            count++;

            if (*cur == ' ') {
                *cur = '\0';
                cur++;
            }
        }

        if (count == 1) {
            fputs(words[0], out);
            fputc('\n', out);
            continue;
        }

        int gaps = count - 1;
        int min_len = sum_len + gaps;

        if ((size_t)min_len >= target) {
            for (int i = 0; i < count; i++) {
                fputs(words[i], out);
                if (i < count - 1) {
                    fputc(' ', out);
                }
            }
            fputc('\n', out);
        } else {
            int extra = (int)target - min_len;
            int base = extra / gaps;
            int rem = extra % gaps;

            for (int i = 0; i < count; i++) {
                fputs(words[i], out);
                if (i < count - 1) {
                    int spaces = 1 + base + (i < rem ? 1 : 0);
                    for (int s = 0; s < spaces; s++) {
                        fputc(' ', out);
                    }
                }
            }
            fputc('\n', out);
        }
    }

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}