// LR_11_task2.c
#include <stdio.h>
#include <time.h>
#include <ctype.h>

// удаление комментариев из входного файла
void remove_comments(FILE *in, FILE *out) {
    enum {
        ST_CODE,
        ST_SLASH,
        ST_LINE_COMMENT,
        ST_BLOCK_COMMENT,
        ST_BLOCK_STAR,
        ST_STRING,
        ST_CHAR,
        ST_STRING_ESC,
        ST_CHAR_ESC
    } st = ST_CODE;

    int c;
    while ((c = fgetc(in)) != EOF) {
        switch (st) {
        case ST_CODE:
            if (c == '/') {
                st = ST_SLASH;
            } else if (c == '"') {
                st = ST_STRING;
                fputc(c, out);
            } else if (c == '\'') {
                st = ST_CHAR;
                fputc(c, out);
            } else {
                fputc(c, out);
            }
            break;

        case ST_SLASH:
            if (c == '/') {
                st = ST_LINE_COMMENT;
            } else if (c == '*') {
                st = ST_BLOCK_COMMENT;
            } else {
                fputc('/', out);
                fputc(c, out);
                st = ST_CODE;
            }
            break;

        case ST_LINE_COMMENT:
            if (c == '\n') {
                fputc('\n', out);
                st = ST_CODE;
            }
            break;

        case ST_BLOCK_COMMENT:
            if (c == '*') {
                st = ST_BLOCK_STAR;
            } else if (c == '\n') {
                fputc('\n', out);
            }
            break;

        case ST_BLOCK_STAR:
            if (c == '/') {
                st = ST_CODE;
            } else if (c == '*') {
                st = ST_BLOCK_STAR;
            } else {
                if (c == '\n') {
                    fputc('\n', out);
                }
                st = ST_BLOCK_COMMENT;
            }
            break;

        case ST_STRING:
            fputc(c, out);
            if (c == '\\') {
                st = ST_STRING_ESC;
            } else if (c == '"') {
                st = ST_CODE;
            }
            break;

        case ST_CHAR:
            fputc(c, out);
            if (c == '\\') {
                st = ST_CHAR_ESC;
            } else if (c == '\'') {
                st = ST_CODE;
            }
            break;

        case ST_STRING_ESC:
            fputc(c, out);
            st = ST_STRING;
            break;

        case ST_CHAR_ESC:
            fputc(c, out);
            st = ST_CHAR;
            break;
        }
    }

    if (st == ST_SLASH) {
        fputc('/', out);
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

    remove_comments(in, out);

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
