#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// свой тип для больших дробных чисел
typedef struct {
    uint64_t int_part;   
    uint64_t frac_part;
    int sign; // 1 -> >0, 0 -> 0, -1 -> <0
} MyFloat;

#define FRAC_BASE ((uint64_t)10000000000000000000ULL) // 10^19 - беру меньше максимального, чтобы не было переполнения

int compare_abs(MyFloat a, MyFloat b);
void normalize(MyFloat *f);
MyFloat add(MyFloat a, MyFloat b);
MyFloat sub(MyFloat a, MyFloat b);

int compare_abs(MyFloat a, MyFloat b) { // a > b -> 1, a == b -> 0, a < b -> -1
    if (a.int_part > b.int_part) {
        return 1;
    }
    if (a.int_part < b.int_part) {
        return -1;
    }
    if (a.frac_part > b.frac_part) {
        return 1;
    }
    if (a.frac_part < b.frac_part) {
        return -1;
    }
    return 0;
}

// нормализация, если дробная часть уже переполнилась (т.е. стала больше единицы, но благодаря запуска в FRAC_BASE ещё помещается в базе)
void normalize(MyFloat *f) {
    if (f->frac_part >= FRAC_BASE) {
        f->int_part += f->frac_part / FRAC_BASE;
        f->frac_part %= FRAC_BASE;
    }
}

MyFloat add(MyFloat a, MyFloat b) {
    MyFloat out;
    if (a.sign == 1 && b.sign == 1) {
        out.int_part = a.int_part + b.int_part;
        out.frac_part = a.frac_part + b.frac_part;
        normalize(&out); // если дробная часть "переполнилась"
        return out;
    }
    if (a.sign == 1 && b.sign == -1) {
        b.sign = 1;
        return sub(a, b);
    }
    if (a.sign == -1 && b.sign == 1) {
        a.sign = 1;
        return sub(b, a);
    }
    if (a.sign == -1 && b.sign == -1) {
        a.sign = 1;
        b.sign = 1;
        out = add(a, b);
        out.sign = -1;
        return out;
    }
    if (a.sign == 0) {
        return b;
    }
    return a;
}

MyFloat sub(MyFloat a, MyFloat b) {
    if (b.sign == 0) {
        return a;
    }
    if (a.sign == 0) {
        b.sign = b.sign * (-1);
        return b;
    }

    MyFloat out;
    int cmp = compare_abs(a, b);

    if (cmp == 1) {
        if (a.sign == 1 && b.sign == 1) {
            out.sign = 1;
            if (a.frac_part < b.frac_part) { // в этом случае нужно занять разряд у целой части
                out.int_part = a.int_part - b.int_part - 1;
                out.frac_part = FRAC_BASE + a.frac_part - b.frac_part;
            } else {
                out.int_part = a.int_part - b.int_part;
                out.frac_part = a.frac_part - b.frac_part;
            }
            out.sign = 1;
            return out;
        }
        if (a.sign == 1 && b.sign == -1) {
            b.sign = 1;
            return add(a, b);
        }
        if (a.sign == -1 && b.sign == 1) {
            a.sign = 1;
            out = add(a, b);
            out.sign = -1;
            return out;
        }
        if (a.sign == -1 && b.sign == -1) {
            a.sign = 1;
            b.sign = 1;
            out = sub(a, b);
            out.sign = -1;
            return out;
        }
    } else if (cmp == -1) {

        if (a.sign == 1 && b.sign == 1) {
            if (b.frac_part < a.frac_part) { // в этом случае нужно занять разряд у целой части
                out.int_part = b.int_part - a.int_part - 1;
                out.frac_part = FRAC_BASE + b.frac_part - a.frac_part;
            } else {
                out.int_part = b.int_part - a.int_part;
                out.frac_part = b.frac_part - a.frac_part;
            }
            out.sign = -1;
            return out;
        }
        if (a.sign == 1 && b.sign == -1) {
            b.sign = 1;
            return add(a, b);
        }
        if (a.sign == -1 && b.sign == 1) {
            a.sign = 1;
            out = add(a, b);
            out.sign = -1;
            return out;
        }
        if (a.sign == -1 && b.sign == -1) {
            b.sign = 1;
            return sub(b, a);
        }
    }   

    out.sign = 0; 
    out.int_part = a.int_part - b.int_part;
    out.frac_part = a.frac_part - b.frac_part;
    return out;
}

void printMyFloat(MyFloat num) {
    if (num.sign == -1) {
        printf("-");
    }
    printf("%" PRIu64 ".%019" PRIu64, num.int_part, num.frac_part); // ".%019" - помогает распечатать расширить до 19 нулей (обсуждали на перемене:3)
}

int main() {
    MyFloat b = {2345, 5749200000000000000ULL, 1}; // 10.5
    MyFloat a = {62345, 9999900000000000000ULL, 1};  // 21.15
    MyFloat c = {0, 0000000000000000000ULL, 0}; // 0.0

    printf("a = "); 
    printMyFloat(a); 
    printf("\n");
    printf("b = "); 
    printMyFloat(b); 
    printf("\n");

    MyFloat sum = add(a, b);
    MyFloat diff = sub(a, b);
    MyFloat sumWithNull = add(a, c);
    MyFloat diffWithNull = sub(a, c);

    printf("a + b = "); 
    printMyFloat(sum); 
    printf("\n");
    printf("a - b = "); 
    printMyFloat(diff); 
    printf("\n");
    printf("a + 0 = "); 
    printMyFloat(sumWithNull); 
    printf("\n");
    printf("a - 0 = "); 
    printMyFloat(diffWithNull); 
    printf("\n");

    return 0;
}
