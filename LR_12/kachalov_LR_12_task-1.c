// вычисление функций через ряды Тейлора
#include <stdio.h>
#include <math.h>
#include <time.h>

#define EPS 1e-6

// значения A и M для шести вариантов
typedef struct {
    double A;
    int M;
} Params;

// вычисление значения ряда sin(x) по N членам
double series_sin(double x, int N) {
    double term = x;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        double factor = -x * x / ((2.0 * k + 2.0) * (2.0 * k + 3.0));
        term *= factor;
        sum += term;
    }
    return sum;
}

// вычисление значения ряда exp(x) по N членам
double series_exp(double x, int N) {
    double term = 1.0;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        term *= x / (double)(k + 1);
        sum += term;
    }
    return sum;
}

// вычисление значения ряда cos(x) по N членам
double series_cos(double x, int N) {
    double term = 1.0;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        double factor = -x * x / ((2.0 * k + 1.0) * (2.0 * k + 2.0));
        term *= factor;
        sum += term;
    }
    return sum;
}

// вычисление значения ряда sinh(x) по N членам
double series_sinh(double x, int N) {
    double term = x;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        double factor = x * x / ((2.0 * k + 2.0) * (2.0 * k + 3.0));
        term *= factor;
        sum += term;
    }
    return sum;
}

// вычисление значения ряда cosh(x) по N членам
double series_cosh(double x, int N) {
    double term = 1.0;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        double factor = x * x / ((2.0 * k + 1.0) * (2.0 * k + 2.0));
        term *= factor;
        sum += term;
    }
    return sum;
}

// вычисление значения ряда sin(x)/x по N членам
double series_sinx_over_x(double x, int N) {
    if (x == 0.0) {
        return 1.0;
    }
    double term = 1.0;
    double sum = term;
    for (int k = 0; k < N - 1; k++) {
        double factor = -x * x / ((2.0 * k + 2.0) * (2.0 * k + 3.0));
        term *= factor;
        sum += term;
    }
    return sum;
}

// поиск минимального N для заданной функции и A при точности EPS
int find_N(int func_id, double A) {
    double x = A;
    int N = 1;
    while (1) {
        double approx;
        double exact;
        switch (func_id) {
        case 1:
            approx = series_sin(x, N);
            exact = sin(x);
            break;
        case 2:
            approx = series_exp(x, N);
            exact = exp(x);
            break;
        case 3:
            approx = series_cos(x, N);
            exact = cos(x);
            break;
        case 4:
            approx = series_sinh(x, N);
            exact = sinh(x);
            break;
        case 5:
            approx = series_cosh(x, N);
            exact = cosh(x);
            break;
        case 6:
            approx = series_sinx_over_x(x, N);
            exact = (x == 0.0) ? 1.0 : sin(x) / x;
            break;
        default:
            return 1;
        }
        if (fabs(approx - exact) < EPS) {
            return N;
        }
        N++;
        if (N > 100000) {
            return N;
        }
    }
}

// вычисление значения ряда выбранной функции
double series_value(int func_id, double x, int N) {
    switch (func_id) {
    case 1:
        return series_sin(x, N);
    case 2:
        return series_exp(x, N);
    case 3:
        return series_cos(x, N);
    case 4:
        return series_sinh(x, N);
    case 5:
        return series_cosh(x, N);
    case 6:
        return series_sinx_over_x(x, N);
    default:
        return 0.0;
    }
}

// библиотечное значение выбранной функции
double library_value(int func_id, double x) {
    switch (func_id) {
    case 1:
        return sin(x);
    case 2:
        return exp(x);
    case 3:
        return cos(x);
    case 4:
        return sinh(x);
    case 5:
        return cosh(x);
    case 6:
        return (x == 0.0) ? 1.0 : sin(x) / x;
    default:
        return 0.0;
    }
}

// печать таблицы значений
void print_table(int func_id, double A, int M, int N) {
    double h = (M > 1) ? A / (double)(M - 1) : 0.0;

    printf("N = %d, A = %.3f, M = %d\n", N, A, M);
    printf("x           S_N(x)        F(x)          |S_N-F|\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < M; i++) {
        double x = h * i;
        double s = series_value(func_id, x, N);
        double f = library_value(func_id, x);
        double diff = fabs(s - f);
        printf("%-10.4f %-12.6f %-12.6f %-12.6f\n", x, s, f, diff);
    }
}

// точка входа
int main(void) {
    clock_t start = clock();

    Params params[6] = {
        {3.0, 4},
        {4.0, 5},
        {3.0, 4},
        {3.0, 4},
        {4.0, 5},
        {5.0, 6}
    };

    int func_id;
    printf("Выберите функцию (1..6):\n");
    printf("1: sin(x)\n");
    printf("2: exp(x)\n");
    printf("3: cos(x)\n");
    printf("4: sinh(x)\n");
    printf("5: cosh(x)\n");
    printf("6: sin(x)/x\n");
    printf("Ваш выбор: ");
    if (scanf("%d", &func_id) != 1 || func_id < 1 || func_id > 6) {
        printf("Некорректный номер варианта.\n");
        return 1;
    }

    double A = params[func_id - 1].A;
    int M = params[func_id - 1].M;

    int N = find_N(func_id, A);
    print_table(func_id, A, M, N);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", seconds);

    return 0;
}
