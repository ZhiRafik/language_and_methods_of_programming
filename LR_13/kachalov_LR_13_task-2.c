// вычисление определённых интегралов методом Симпсона
#include <stdio.h>
#include <math.h>
#include <time.h>

#define EPS 0.0005
#define PI  3.14159265358979323846

// первая функция: e^x * cos(pi*x/4)
double g1(double x) {
    return exp(x) * cos(PI * x / 4.0);
}

// вторая функция: 1 / tg(x)
double g2(double x) {
    return 1.0 / tan(x);
}

// третья функция: e^x / x
double g3(double x) {
    return exp(x) / x;
}

// четвёртая функция: cos(x) / x
double g4(double x) {
    return cos(x) / x;
}

// пятая функция: sqrt(1 + cos^2(x))
double g5(double x) {
    double c = cos(x);
    return sqrt(1.0 + c * c);
}

// шестая функция: e^x * sin^2(x)
double g6(double x) {
    double s = sin(x);
    return exp(x) * s * s;
}

// вычисление интеграла методом Симпсона при заданном n
double simpson(double (*g)(double), double a, double b, int n) {
    double h = (b - a) / (double)n;
    double sum1 = 0.0;
    double sum2 = 0.0;

    for (int k = 1; k < n; k += 2) {
        double x = a + h * k;
        sum1 += g(x);
    }

    for (int k = 2; k < n; k += 2) {
        double x = a + h * k;
        sum2 += g(x);
    }

    double result = (h / 3.0) * (g(a) + g(b) + 4.0 * sum1 + 2.0 * sum2);
    return result;
}

// выбор функции по номеру
double eval_g(int id, double x) {
    switch (id) {
    case 1: return g1(x);
    case 2: return g2(x);
    case 3: return g3(x);
    case 4: return g4(x);
    case 5: return g5(x);
    case 6: return g6(x);
    default: return 0.0;
    }
}

int main(void) {
    clock_t start = clock();

    int id;
    printf("Выберите интеграл (1..6): ");
    if (scanf("%d", &id) != 1 || id < 1 || id > 6) {
        printf("Некорректный номер.\n");
        return 1;
    }

    double a[6] = {0.0, PI / 6.0, 1.0, PI / 2.0, 0.0, 0.0};
    double b[6] = {2.0, PI / 2.0, 7.0, PI,       PI, 5.0};

    double (*g)(double) = NULL;
    switch (id) {
    case 1: g = g1; break;
    case 2: g = g2; break;
    case 3: g = g3; break;
    case 4: g = g4; break;
    case 5: g = g5; break;
    case 6: g = g6; break;
    }

    int n = 10;
    if (n % 2 != 0) {
        n++;
    }

    double I_prev = simpson(g, a[id - 1], b[id - 1], n);
    while (1) {
        n *= 2;
        double I_curr = simpson(g, a[id - 1], b[id - 1], n);
        if (fabs(I_curr - I_prev) < EPS) {
            I_prev = I_curr;
            break;
        }
        I_prev = I_curr;
        if (n > 1000000) {
            break;
        }
    }

    printf("Интеграл варианта %d\n", id);
    printf("Отрезок: [%.6f, %.6f]\n", a[id - 1], b[id - 1]);
    printf("Число разбиений n = %d\n", n);
    printf("Значение интеграла ≈ %.10f\n", I_prev);
    printf("Точность EPS = %.6f\n", EPS);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f с\n", seconds);

    return 0;
}
