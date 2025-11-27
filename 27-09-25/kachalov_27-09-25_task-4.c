#include <stdio.h>
#include <stdint.h>

typedef struct {
    int realPart;
    int complexPart;
} ComplexNumber;

ComplexNumber add(ComplexNumber a, ComplexNumber b) { 
    ComplexNumber res;
    res.realPart = a.realPart + b.realPart;
    res.complexPart = a.complexPart + b.complexPart;
    return res;
}

ComplexNumber sub(ComplexNumber a, ComplexNumber b) {
    ComplexNumber res;
    res.realPart = a.realPart - b.realPart;
    res.complexPart = a.complexPart - b.complexPart;
    return res;
}

void printMyComplexNumber(ComplexNumber a) {
    if (a.complexPart >= 0) {
        printf("%d + %di", a.realPart, a.complexPart);
    } else {
        printf("%d - %di", a.realPart, -a.complexPart);
    }
}

int main() {
    ComplexNumber a = {5050, -2020};
    ComplexNumber b = {-2070, 3055};

    ComplexNumber sum = add(a, b);
    ComplexNumber diffAB = sub(a, b);
    ComplexNumber diffBA = sub(b, a);

    printf("a = "); printMyComplexNumber(a); printf("\n");
    printf("b = "); printMyComplexNumber(b); printf("\n");
    printf("a + b = "); printMyComplexNumber(sum); printf("\n");
    printf("a - b = "); printMyComplexNumber(diffAB); printf("\n");
    printf("b - a = "); printMyComplexNumber(diffBA); printf("\n");
}