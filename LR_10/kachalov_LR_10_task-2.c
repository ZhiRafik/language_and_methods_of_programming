// LR_10_task2.c
#include <stdio.h>
#include <time.h>

// реверс бит в байте
unsigned char reverse_bits(unsigned char b) {
    unsigned char r = 0;
    for (int i = 0; i < 8; i++) {
        if (b & (1u << i)) {
            r |= 1u << (7 - i);
        }
    }
    return r;
}

// шифрование и дешифрование файла
int main(void) {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    if (!in) {
        perror("input.txt");
        return 1;
    }

    FILE *enc = fopen("encrypted.bin", "wb");
    if (!enc) {
        perror("encrypted.bin");
        fclose(in);
        return 1;
    }

    int c;
    while ((c = fgetc(in)) != EOF) {
        unsigned char ch = (unsigned char)c;

        if (ch == '\t') {
            for (int i = 0; i < 4; i++) {
                unsigned char sp = ' ';
                unsigned char e = reverse_bits(sp);
                fputc(e, enc);
            }
        } else {
            unsigned char e = reverse_bits(ch);
            fputc(e, enc);
        }
    }

    fclose(in);
    fclose(enc);

    enc = fopen("encrypted.bin", "rb");
    if (!enc) {
        perror("encrypted.bin");
        return 1;
    }

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        perror("output.txt");
        fclose(enc);
        return 1;
    }

    while ((c = fgetc(enc)) != EOF) {
        unsigned char ch = (unsigned char)c;
        unsigned char d = reverse_bits(ch);
        fputc(d, out);
    }

    fclose(enc);
    fclose(out);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
