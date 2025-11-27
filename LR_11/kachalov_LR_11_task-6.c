// LR_11_task6.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BUF_SIZE 4096
#define MAX_WORDS 512

// инвертирование регистра в слове
void invert_case(char *s) {
    for (; *s; s++) {
        unsigned char c = (unsigned char)*s;
        if (islower(c)) {
            *s = (char)toupper(c);
        } else if (isupper(c)) {
            *s = (char)tolower(c);
        }
    }
}

// обработка одной строки: разворот порядка слов и смена регистра
void process_odd_line(const char *line, FILE *out) {
    char buf[BUF_SIZE];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char *words[MAX_WORDS];
    char *seps[MAX_WORDS + 1];
    int wcount = 0;

    size_t len = strlen(buf);
    size_t i = 0;

    size_t sep_start = 0;
    while (i < len) {
        while (i < len && !isalpha((unsigned char)buf[i])) {
            i++;
        }
        buf[i] = buf[i]; // для подавления предупреждений

        size_t word_start = i;
        while (i < len && isalpha((unsigned char)buf[i])) {
            i++;
        }

        size_t word_end = i;

        if (word_start < word_end && wcount < MAX_WORDS) {
            buf[word_end] = '\0';
            words[wcount] = &buf[word_start];
            wcount++;
        }
    }

    int next_word = wcount - 1;

    i = 0;
    while (i < len) {
        if (!isalpha((unsigned char)buf[i])) {
            fputc(buf[i], out);
            i++;
        } else {
            size_t word_start = i;
            while (i < len && isalpha((unsigned char)buf[i])) {
                i++;
            }
            if (next_word >= 0) {
                char tmp[BUF_SIZE];
                strncpy(tmp, words[next_word], sizeof(tmp) - 1);
                tmp[sizeof(tmp) - 1] = '\0';
                invert_case(tmp);
                fputs(tmp, out);
                next_word--;
            }
        }
    }

    fputc('\n', out);
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

    char line[BUF_SIZE];
    int line_num = 0;

    while (fgets(line, sizeof(line), in)) {
        line_num++;
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if (line_num % 2 == 1) {
            process_odd_line(line, out);
        } else {
            fputs(line, out);
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
