// решение уравнений: деление пополам и метод хорд
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>

// первая функция: x + ln(x+0.5) - 0.5
double f1(double x) {
    return x + log(x + 0.5) - 0.5;
}

// вторая функция: (2*sin^2(x))/3 - 0.75*cos^2(x)
double f2(double x) {
    double s = sin(x);
    double c = cos(x);
    return (2.0 * s * s) / 3.0 - 0.75 * c * c;
}

// третья функция: x^2 * 2^x - 1
double f3(double x) {
    return x * x * pow(2.0, x) - 1.0;
}

// четвёртая функция: x^2 - sin(5x)
double f4(double x) {
    return x * x - sin(5.0 * x);
}

// пятая функция: (4 + x^2)*e^(-x^2) - 18
double f5(double x) {
    return (4.0 + x * x) * exp(-x * x) - 18.0;
}

// шестая функция: x^2 - 1.3*ln(x+0.5) - 2.8x + 2.35
double f6(double x) {
    return x * x - 1.3 * log(x + 0.5) - 2.8 * x + 2.35;
}

// метод деления отрезка пополам
double root_bisection(double (*f)(double), double a, double b, double eps, int *it) {
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0.0) {
        *it = 0;
        return a;
    }
    int k = 0;
    double c = a;
    while ((b - a) / 2.0 > eps) {
        c = 0.5 * (a + b);
        double fc = f(c);
        if (fa * fc <= 0.0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        k++;
        if (k > 1000000) {
            break;
        }
    }
    *it = k;
    return 0.5 * (a + b);
}

// метод хорд 
double root_secant(double (*f)(double), double x0, double x1, double eps, int *it) {
    double f0 = f(x0);
    double f1 = f(x1);
    int k = 0;
    while (fabs(x1 - x0) > eps && fabs(f1) > eps) {
        double denom = f1 - f0;
        if (fabs(denom) < 1e-15) {
            break;
        }
        double x2 = x1 - f1 * (x1 - x0) / denom;
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
        k++;
        if (k > 1000000) {
            break;
        }
    }
    *it = k;
    return x1;
}

// выбор функции по номеру
double eval_f(int id, double x) {
    switch (id) {
    case 1: return f1(x);
    case 2: return f2(x);
    case 3: return f3(x);
    case 4: return f4(x);
    case 5: return f5(x);
    case 6: return f6(x);
    default: return 0.0;
    }
}

int main(void) {
    clock_t start = clock();

    int id;
    printf("Выберите задачу (1..6): ");
    if (scanf("%d", &id) != 1 || id < 1 || id > 6) {
        printf("Некорректный номер.\n");
        return 1;
    }

    double a[6] = {0.0, 0.0, 0.0, 0.5, 1.2, 1.7};
    double b[6] = {2.0, M_PI / 2.0, 1.0, 0.6, 1.3, 2.7};
    double eps = 2.0f * FLT_EPSILON;

    double (*f)(double) = NULL;
    switch (id) {
    case 1: f = f1; break;
    case 2: f = f2; break;
    case 3: f = f3; break;
    case 4: f = f4; break;
    case 5: f = f5; break;
    case 6: f = f6; break;
    }

    double root = 0.0;
    int iters = 0;

    if (id == 1 || id == 3 || id == 5) {
        root = root_bisection(f, a[id - 1], b[id - 1], eps, &iters);
        printf("Метод деления пополам\n");
    } else {
        root = root_secant(f, a[id - 1], b[id - 1], eps, &iters);
        printf("Метод хорд (secant)\n");
    }

    printf("Интервал: [%.6f, %.6f]\n", a[id - 1], b[id - 1]);
    printf("Корень x = %.10f\n", root);
    printf("f(x) = %.10e\n", eval_f(id, root));
    printf("Итераций: %d\n", iters);
    printf("eps = %.10e\n", eps);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f с\n", seconds);

    return 0;
}
