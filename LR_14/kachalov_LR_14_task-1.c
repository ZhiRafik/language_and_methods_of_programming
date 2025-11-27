// построение графика функции на экране и гистограммы в файле
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 78   // ширина экрана по X
#define HEIGHT 25  // высота экрана по Y
#define FILE_X 60  // высота гистограммы (ось X вертикально)
#define FILE_Y 80  // ширина гистограммы (ось Y горизонтально)

// вычисление функции по варианту
double func(int id, double x) {
    switch (id) {
    case 1:
        return fabs(2.0 * sin(x)) - fabs(cos(3.0 * x));
    case 2:
        return 2.0 * sin(x) + 3.0 * cos(2.0 * x);
    case 3:
        return (x - 3.0) / (x * x + 2.0);
    case 4:
        return x * x * exp(-x);
    case 5:
        return exp(-x) * sin(2.0 * x);
    case 6:
        return pow(fabs(x + 2.0), 2.0 / 3.0) - pow(fabs(x - 2.0), 2.0 / 3.0);
    default:
        return 0.0;
    }
}

// поиск минимума и максимума функции на отрезке
void find_range(int id, double xmin, double xmax, double *ymin, double *ymax) {
    int steps = 2000;
    double dx = (xmax - xmin) / steps;
    double x = xmin;
    double y = func(id, x);
    double minv = y;
    double maxv = y;

    for (int i = 1; i <= steps; i++) {
        x = xmin + dx * i;
        y = func(id, x);
        if (y < minv) {
            minv = y;
        }
        if (y > maxv) {
            maxv = y;
        }
    }

    *ymin = minv;
    *ymax = maxv;

    if (fabs(*ymax - *ymin) < 1e-12) {
        *ymax = *ymin + 1.0;
    }
}

// построение графика на экране
void draw_screen_plot(int id, double xmin, double xmax, double ymin, double ymax) {
    char canvas[HEIGHT][WIDTH];

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            canvas[r][c] = ' ';
        }
    }

    double dx = (xmax - xmin) / (WIDTH - 1);
    double dy = (ymax - ymin) / (HEIGHT - 1);

    int x0_col = -1;
    int y0_row = -1;

    if (xmin <= 0.0 && 0.0 <= xmax) {
        x0_col = (int)round((0.0 - xmin) / dx);
    }
    if (ymin <= 0.0 && 0.0 <= ymax) {
        y0_row = (int)round((ymax - 0.0) / dy);
    }

    if (y0_row >= 0 && y0_row < HEIGHT) {
        for (int c = 0; c < WIDTH; c++) {
            canvas[y0_row][c] = '-';
        }
    }
    if (x0_col >= 0 && x0_col < WIDTH) {
        for (int r = 0; r < HEIGHT; r++) {
            canvas[r][x0_col] = '|';
        }
    }

    for (int c = 0; c < WIDTH; c++) {
        double x = xmin + dx * c;
        double y = func(id, x);
        int r = (int)round((ymax - y) / dy);
        if (r >= 0 && r < HEIGHT) {
            canvas[r][c] = '*';
        }
    }

    if (x0_col >= 0 && y0_row >= 0 && x0_col < WIDTH && y0_row < HEIGHT) {
        canvas[y0_row][x0_col] = '+';
    }

    printf("График функции на экране:\n");
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            putchar(canvas[r][c]);
        }
        putchar('\n');
    }
}

// построение гистограммы в файле
void draw_histogram_file(const char *filename, int id,
                         double xmin, double xmax,
                         double ymin, double ymax) {
    char hist[FILE_X][FILE_Y];

    for (int r = 0; r < FILE_X; r++) {
        for (int c = 0; c < FILE_Y; c++) {
            hist[r][c] = ' ';
        }
    }

    double dx = (xmax - xmin) / (FILE_X - 1);
    double dy = (ymax - ymin) / (FILE_Y - 1);

    int x0_row = -1;
    int y0_col = -1;

    if (xmin <= 0.0 && 0.0 <= xmax) {
        x0_row = (int)round((0.0 - xmin) / dx);
    }
    if (ymin <= 0.0 && 0.0 <= ymax) {
        y0_col = (int)round((0.0 - ymin) / dy);
    }

    if (x0_row >= 0 && x0_row < FILE_X) {
        for (int c = 0; c < FILE_Y; c++) {
            hist[x0_row][c] = '-';
        }
    }
    if (y0_col >= 0 && y0_col < FILE_Y) {
        for (int r = 0; r < FILE_X; r++) {
            hist[r][y0_col] = '|';
        }
    }

    double values[FILE_X];

    for (int r = 0; r < FILE_X; r++) {
        double x = xmin + dx * r;
        double y = func(id, x);
        values[r] = y;

        int col = (int)round((y - ymin) / dy);
        if (col < 0) {
            col = 0;
        }
        if (col >= FILE_Y) {
            col = FILE_Y - 1;
        }

        int start, end;

        if (y0_col >= 0 && y0_col < FILE_Y) {
            start = y0_col;
            end = col;
        } else {
            start = 0;
            end = col;
        }

        if (start > end) {
            int tmp = start;
            start = end;
            end = tmp;
        }

        for (int c = start; c <= end; c++) {
            if (hist[r][c] == ' ' || hist[r][c] == '-' || hist[r][c] == '|') {
                hist[r][c] = '#';
            }
        }
    }

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("histogram file");
        return;
    }

    for (int r = FILE_X - 1; r >= 0; r--) {
        for (int c = 0; c < FILE_Y; c++) {
            fputc(hist[r][c], f);
        }
        fprintf(f, "  %.3f\n", values[r]);
    }

    fprintf(f, "Масштаб по Y: dy = %.6f\n", dy);
    fclose(f);
}

int main(void) {
    clock_t start = clock();

    int id;
    printf("Выберите вариант (1..6): ");
    if (scanf("%d", &id) != 1 || id < 1 || id > 6) {
        printf("Некорректный номер варианта.\n");
        return 1;
    }

    double xmin, xmax;

    switch (id) {
    case 1:
        xmin = -M_PI / 2.0;
        xmax = M_PI;
        break;
    case 2:
        xmin = -M_PI / 2.0;
        xmax = M_PI / 2.0;
        break;
    case 3:
        xmin = -1.0;
        xmax = 4.0;
        break;
    case 4:
        xmin = -1.0;
        xmax = 2.0;
        break;
    case 5:
        xmin = -M_PI / 2.0;
        xmax = 2.0 * M_PI;
        break;
    case 6:
        xmin = -3.0;
        xmax = 2.5;
        break;
    default:
        xmin = 0.0;
        xmax = 1.0;
        break;
    }

    double ymin, ymax;
    find_range(id, xmin, xmax, &ymin, &ymax);

    draw_screen_plot(id, xmin, xmax, ymin, ymax);
    draw_histogram_file("histogram.txt", id, xmin, xmax, ymin, ymax);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);
    printf("Гистограмма записана в файл histogram.txt\n");

    return 0;
}
