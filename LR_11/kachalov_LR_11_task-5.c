// LR_11_task5.c
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// проверка символа идентификатора
int is_ident_char(int c) {
    return isalnum(c) || c == '_';
}

// замена ключевых слов int/char вне строк и комментариев
void replace_types(FILE *in, FILE *out) {
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
            } else if (isalpha(c) || c == '_') {
                char buf[256];
                int pos = 0;
                buf[pos++] = (char)c;
                while ((c = fgetc(in)) != EOF &&
                       (isalnum(c) || c == '_')) {
                    if (pos + 1 < (int)sizeof(buf)) {
                        buf[pos++] = (char)c;
                    }
                }
                buf[pos] = '\0';

                if (strcmp(buf, "int") == 0) {
                    fputs("integer", out);
                } else if (strcmp(buf, "char") == 0) {
                    fputs("character", out);
                } else {
                    fputs(buf, out);
                }

                if (c == EOF) {
                    break;
                }
                fputc(c, out);
            } else {
                fputc(c, out);
            }
            break;

        case ST_SLASH:
            if (c == '/') {
                fputc('/', out);
                fputc('/', out);
                st = ST_LINE_COMMENT;
            } else if (c == '*') {
                fputc('/', out);
                fputc('*', out);
                st = ST_BLOCK_COMMENT;
            } else {
                fputc('/', out);
                fputc(c, out);
                st = ST_CODE;
            }
            break;

        case ST_LINE_COMMENT:
            fputc(c, out);
            if (c == '\n') {
                st = ST_CODE;
            }
            break;

        case ST_BLOCK_COMMENT:
            fputc(c, out);
            if (c == '*') {
                st = ST_BLOCK_STAR;
            }
            break;

        case ST_BLOCK_STAR:
            fputc(c, out);
            if (c == '/') {
                st = ST_CODE;
            } else if (c != '*') {
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

    replace_types(in, out);

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
