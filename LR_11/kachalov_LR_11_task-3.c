// LR_11_task3.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// проверка, что строка является ключевым словом C
int is_keyword(const char *s) {
    const char *kw[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while",
        "_Bool", "_Complex", "_Imaginary"
    };
    int n = (int)(sizeof(kw) / sizeof(kw[0]));
    for (int i = 0; i < n; i++) {
        if (strcmp(s, kw[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// подсчёт идентификаторов в исходнике C
int count_identifiers(FILE *in) {
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
    int count = 0;

    while ((c = fgetc(in)) != EOF) {
        switch (st) {
        case ST_CODE:
            if (c == '/') {
                st = ST_SLASH;
            } else if (c == '"') {
                st = ST_STRING;
            } else if (c == '\'') {
                st = ST_CHAR;
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
                if (!is_keyword(buf)) {
                    count++;
                }
                if (c == EOF) {
                    break;
                }
                ungetc(c, in);
            }
            break;

        case ST_SLASH:
            if (c == '/') {
                st = ST_LINE_COMMENT;
            } else if (c == '*') {
                st = ST_BLOCK_COMMENT;
            } else {
                st = ST_CODE;
            }
            break;

        case ST_LINE_COMMENT:
            if (c == '\n') {
                st = ST_CODE;
            }
            break;

        case ST_BLOCK_COMMENT:
            if (c == '*') {
                st = ST_BLOCK_STAR;
            }
            break;

        case ST_BLOCK_STAR:
            if (c == '/') {
                st = ST_CODE;
            } else if (c != '*') {
                st = ST_BLOCK_COMMENT;
            }
            break;

        case ST_STRING:
            if (c == '\\') {
                st = ST_STRING_ESC;
            } else if (c == '"') {
                st = ST_CODE;
            }
            break;

        case ST_CHAR:
            if (c == '\\') {
                st = ST_CHAR_ESC;
            } else if (c == '\'') {
                st = ST_CODE;
            }
            break;

        case ST_STRING_ESC:
            st = ST_STRING;
            break;

        case ST_CHAR_ESC:
            st = ST_CHAR;
            break;
        }
    }

    return count;
}

int main(void) {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    int cnt = count_identifiers(in);
    fclose(in);

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        perror("output.txt");
        return 1;
    }

    fprintf(out, "Identifiers: %d\n", cnt);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
