#include <stdio.h>

// используем тернарку и арифметику
int findMinForXYZ(int x, int y, int z) {
    return x < y ? (x < z ? x : z) : (y < z ? y : z); 
}

int findSpecialMaxForXYZ(int x, int y, int z) {
    return x + y + z > x * y * z ? (x + y + z) : (x * y * z);
}

void changePair(int *x, int *y) {
    int halfSum = (*x + *y) / 2;
    int product = *x * *y;
    *x < *y ? (
        (void)(*x = halfSum, *y = product)
    ) : (void)0;
}

void changeGroup(int *x, int *y, int *z) {
    int halfSum = (*x + *y + *z) / 2;
    *x + *y + *z < 1 ? (
        *x < *y ? (*x < *z ? (void)(*x = halfSum) : (void)(*z = halfSum)) 
        : (*y < *z ? (void)(*y = halfSum) : (void)(*z = halfSum)) 
    ) : (*x < *y ? (void)(*x = halfSum) : (void)(*y = halfSum));
}

int findZ(int x, int y) {
    return x > y ? x - y : y - x + 1;
}

void helpToFindAbsolute(int *x, int *y, int *z) {
    *x < 0 ? (void)(*x = -*x) : (void)0;
    *y < 0 ? (void)(*y = -*y) : (void)0;
    *z < 0 ? (void)(*z = -*z) : (void)0;
}

void maybeDoubleGroupOrFindAbsolute(int *x, int *y, int *z) {
    *x > *y ? (
        *y > *z ? (
            (void)(*x = *x * 2, *y = *y * 2, *z = *z * 2)
        ) : helpToFindAbsolute(x, y, z)
    ) : helpToFindAbsolute(x, y, z);
}

int findMaxForXYZ(int x, int y, int z) {
    return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

int calculateSpecialMinPowerTwoInGroup(int x, int y, int z) {
    int specialMin = (x + y + z) / 2 < (x * y * z) ?
        (x + y + z) / 2 :
        (x * y * z);
    return specialMin * specialMin + 1;
} 

int main() {
    int x, y, z;
    printf("Введите три числа: ");
    scanf("%d %d %d", &x, &y, &z);

    // функции, возвращающие значения
    printf("findMinForXYZ : %d\n", findMinForXYZ(x, y, z));
    printf("findSpecialMaxForXYZ : %d\n", findSpecialMaxForXYZ(x, y, z));
    printf("findZ : %d\n", findZ(x, y));
    printf("findMaxForXYZ : %d\n", findMaxForXYZ(x, y, z));
    printf("calculateSpecialMinPowerTwoInGroup : %d\n", calculateSpecialMinPowerTwoInGroup(x, y, z));

    // функции, которые меняют по указателям
    int a = x, b = y; int c;
    changePair(&a, &b);
    printf("changePair : x=%d y=%d\n", a, b);

    a = x; b = y; c = z;
    changeGroup(&a, &b, &c);
    printf("changeGroup : x=%d y=%d z=%d\n", a, b, c);

    a = x; b = y; c = z;
    helpToFindAbsolute(&a, &b, &c);
    printf("helpToFindAbsolute : x=%d y=%d z=%d\n", a, b, c);

    a = x; b = y; c = z;
    maybeDoubleGroupOrFindAbsolute(&a, &b, &c);
    printf("maybeDoubleGroupOrFindAbsolute : x=%d y=%d z=%d\n", a, b, c);

    return 0;
}