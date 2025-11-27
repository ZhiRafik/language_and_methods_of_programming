#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start = clock();

    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.bin", "wb");
    char buf[1024];

    if (!in || !out) {
        perror("fopen");
        return 1;
    }

    while (fgets(buf, sizeof(buf), in)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }

        int len_int = (int)len;                // приводим size_t к int
        fwrite(&len_int, sizeof(int), 1, out); // пишем int
        fwrite(buf, sizeof(char), len, out);
    }

    fclose(in);
    fclose(out);

    FILE *f = fopen("output.bin", "rb");
    if (!f) {
        perror("output.bin");
        return 1;
    }

    while (1) {
        int lenn;
        if (fread(&lenn, sizeof(int), 1, f) != 1) break;

        char *buff = malloc(lenn + 1);
        if (!buff) {
            perror("malloc");
            fclose(f);
            return 1;
        }

        if (fread(buff, 1, lenn, f) != (size_t)lenn) {
            free(buff);
            break;
        }
        buff[lenn] = '\0';

        printf("[%d bytes] %s\n", lenn, buff);
        free(buff);
    }

    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
