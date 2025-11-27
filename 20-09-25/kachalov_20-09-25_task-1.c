#include <stdio.h>
// используем только умножение и присваивание!

int getPowerOf7(int a) { // 4 операции
    int a2 = a * a;
    int a4 = a2 * a2;
    int a7 = a4 * a2 * a;
    return a7;
}

int getPowerOf15(int a) { // 5 операции
    int a3 = a * a * a;
    int a6 = a3 * a3;
    int a12 = a6 * a6;
    int a15 = a12 * a3;
    return a15;
}

int getPowerOf8(int a) { // 3 операции
    int a2 = a * a;
    int a4 = a2 * a2;
    int a8 = a4 * a4;
    return a8;
}

int getPowerOf21(int a) { // 6 операции
    int a3 = a * a * a;
    int a6 = a3 * a3;
    int a18 = a6 * a6 * a6;
    int a21 = a18 * a3;
    return a21;
}

int getPowerOf13(int a) { // 5 операции
    int a3 = a * a * a;
    int a6 = a3 * a3;
    int a12 = a6 * a6;
    int a13 = a12 * a;
    return a13;
}

int getPowerOf28(int a) { // 6 операции
    int a2 = a * a;
    int a4 = a2 * a2;
    int a7 = a4 * a2 * a;
    int a14 = a7 * a7;
    int a28 = a14 * a14;
    return a28;
}

int main() {
    int a;
    printf("Введите a для возведений в степени: ");
    scanf("%d", &a);
    int a7 = getPowerOf7(a);
    int a15 = getPowerOf15(a);
    int a8 = getPowerOf8(a);
    int a21 = getPowerOf21(a);
    int a13 = getPowerOf13(a);
    int a28 = getPowerOf28(a);
    printf("a^7 = %d\n", a7);
    printf("a^15 = %d\n", a15);
    printf("a^8 = %d\n", a8);
    printf("a^21 = %d\n", a21);
    printf("a^13 = %d\n", a13);
    printf("a^28 = %d\n", a28);
}