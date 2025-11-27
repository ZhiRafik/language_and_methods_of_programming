// LR_10_task4.c
#include <stdio.h>
#include <string.h>
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

// формирование строк фиксированной длины
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

    size_t target = max_len / 2;
    if (target == 0) {
        target = 1;
    }

    rewind(in);

    char expanded[8192];
    char cur[8192];
    size_t cur_len = 0;

    while (fgets(buf, sizeof(buf), in)) {
        expand_line(buf, expanded, sizeof(expanded));
        size_t len = strlen(expanded);

        for (size_t i = 0; i < len; i++) {
            cur[cur_len++] = expanded[i];
            if (cur_len == target) {
                fwrite(cur, 1, cur_len, out);
                fputc('\n', out);
                cur_len = 0;
            }
        }
    }

    if (cur_len > 0) {
        fwrite(cur, 1, cur_len, out);
        fputc('\n', out);
    }

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
