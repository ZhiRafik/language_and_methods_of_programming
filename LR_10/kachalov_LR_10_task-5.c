// LR_10_task5.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// форматирование текста по правилам задачи
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
    int capitalize_next = 0;

    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        size_t cap = len * 4 + 1;
        char *line = malloc(cap);
        if (!line) {
            perror("malloc");
            fclose(in);
            fclose(out);
            return 1;
        }

        size_t j = 0;

        for (size_t i = 0; i < len; i++) {
            unsigned char c = (unsigned char)buf[i];
            if (c == '\n') {
                break;
            }

            if (c == '\t') {
                for (int k = 0; k < 4; k++) {
                    if (j + 1 < cap) {
                        line[j++] = ' ';
                    }
                }
                continue;
            }

            if (isalnum(c)) {
                if (capitalize_next && isalpha(c)) {
                    c = (unsigned char)toupper(c);
                }
                if (j + 1 < cap) {
                    line[j++] = (char)c;
                }
                capitalize_next = 0;
            } else {
                if (j + 1 < cap) {
                    line[j++] = (char)c;
                }
                if (j + 1 < cap) {
                    line[j++] = ' ';
                }
                if (c == '.') {
                    capitalize_next = 1;
                }
            }
        }

        line[j] = '\0';
        fprintf(out, "%s\n", line);
        free(line);
    }

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
