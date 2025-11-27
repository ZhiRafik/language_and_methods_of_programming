// LR_11_task1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BUF_SIZE 4096

// проверка символа идентификатора
int is_ident_char(int c) {
    return isalnum(c) || c == '_';
}

// обработка одной строки: замена hex <-> dec для токенов
void process_line(const char *line, FILE *out) {
    size_t i = 0;
    size_t n = strlen(line);

    while (i < n) {
        char c = line[i];

        // попытка hex-токена 0x...
        if (c == '0' && i + 2 < n && (line[i + 1] == 'x' || line[i + 1] == 'X')) {
            int prev = (i == 0) ? 0 : line[i - 1];
            if (!is_ident_char(prev)) {
                size_t j = i + 2;
                if (j < n && isxdigit((unsigned char)line[j])) {
                    while (j < n && isxdigit((unsigned char)line[j])) {
                        j++;
                    }
                    int next = (j < n) ? line[j] : 0;
                    if (!is_ident_char(next)) {
                        char numbuf[64];
                        strncpy(numbuf, line + i, j - i);
                        numbuf[j - i] = '\0';
                        unsigned long val = strtoul(numbuf, NULL, 16);

                        char outbuf[64];
                        sprintf(outbuf, "%lu", val);
                        fputs(outbuf, out);

                        i = j;
                        continue;
                    }
                }
            }
        }

        // попытка десятичного токена
        if (isdigit((unsigned char)c)) {
            int prev = (i == 0) ? 0 : line[i - 1];
            if (!is_ident_char(prev)) {
                size_t j = i;
                while (j < n && isdigit((unsigned char)line[j])) {
                    j++;
                }
                int next = (j < n) ? line[j] : 0;
                if (!is_ident_char(next)) {
                    char numbuf[64];
                    size_t len = j - i;
                    if (len >= sizeof(numbuf)) {
                        len = sizeof(numbuf) - 1;
                    }
                    strncpy(numbuf, line + i, len);
                    numbuf[len] = '\0';

                    unsigned long val = strtoul(numbuf, NULL, 10);

                    char outbuf[64];
                    sprintf(outbuf, "0x%lX", val);
                    fputs(outbuf, out);

                    i = j;
                    continue;
                }
            }
        }

        // обычный символ
        fputc(c, out);
        i++;
    }
}

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

    char buf[BUF_SIZE];

    while (fgets(buf, sizeof(buf), in)) {
        process_line(buf, out);
    }

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
