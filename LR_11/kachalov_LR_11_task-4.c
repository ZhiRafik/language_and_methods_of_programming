// LR_11_task4.c
#include <stdio.h>
#include <ctype.h>
#include <time.h>

// преобразование текста по правилу нечётных слов
void transform_words(FILE *in, FILE *out) {
    int c;
    int in_word = 0;
    int word_index = 0;
    int first_char = 0;
    int delete_word = 0;

    while ((c = fgetc(in)) != EOF) {
        if (isalpha(c)) {
            if (!in_word) {
                in_word = 1;
                word_index++;
                first_char = c;
                delete_word = 0;
                if (word_index % 2 == 1 && isupper(first_char)) {
                    delete_word = 1;
                }
                if (delete_word) {
                    // просто не печатаем этот и последующие символы слова
                } else if (word_index % 2 == 1) {
                    if (islower(c)) {
                        fputc(toupper(c), out);
                    } else if (isupper(c)) {
                        fputc(tolower(c), out);
                    } else {
                        fputc(c, out);
                    }
                } else {
                    fputc(c, out);
                }
            } else {
                if (delete_word) {
                    // пропускаем
                } else if (word_index % 2 == 1) {
                    if (islower(c)) {
                        fputc(toupper(c), out);
                    } else if (isupper(c)) {
                        fputc(tolower(c), out);
                    } else {
                        fputc(c, out);
                    }
                } else {
                    fputc(c, out);
                }
            }
        } else {
            if (in_word) {
                in_word = 0;
            }
            fputc(c, out);
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

    transform_words(in, out);

    fclose(in);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
