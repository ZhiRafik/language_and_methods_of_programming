#include <stdio.h>
#include <limits.h>

int main() {
    for (int k = 0; k < 6; k++) {
        signed char sc;
        if (k == 0) {
            sc = CHAR_MAX;
            printf("1. processing CHAR_MAX \n");
        } else if (k == 1) {
            sc = UCHAR_MAX;
            printf("processing UCHAR_MAX \n");
        } else if (k == 2) {
            sc = ULONG_MAX;
            printf("processing ULONG_MAX \n");
        } else if (k == 3) {
            sc = LONG_MAX;
            printf("processing LONG_MAX \n");
        } else if (k == 4) {
            sc = CHAR_MIN;
            printf("processing CHAR_MIN \n");
        } else if (k == 5) {
            sc = LONG_MIN;
            printf("processing LONG_MIN \n");
        }
        printf("%c\n", sc);
        signed short int si = sc;
        printf("%hd\n", si);
        signed int i = si;
        printf("%d\n", i);
        signed long l = i;
        printf("%ld\n", l);
    }

    for (int k = 0; k < 6; k++) {
        unsigned char sc;
        if (k == 0) {
            sc = CHAR_MAX;
            printf("1. processing CHAR_MAX \n");
        } else if (k == 1) {
            sc = UCHAR_MAX;
            printf("processing UCHAR_MAX \n");
        } else if (k == 2) {
            sc = ULONG_MAX;
            printf("processing ULONG_MAX \n");
        } else if (k == 3) {
            sc = LONG_MAX;
            printf("processing LONG_MAX \n");
        } else if (k == 4) {
            sc = CHAR_MIN;
            printf("processing CHAR_MIN \n");
        } else if (k == 5) {
            sc = LONG_MIN;
            printf("processing LONG_MIN \n");
        }
        printf("%c\n", sc);
        unsigned short int si = sc;
        printf("%hu\n", si);
        unsigned int i = si;
        printf("%u\n", i);
        unsigned long l = i;
        printf("%lu\n", l);
    }

    for (int k = 0; k < 6; k++) {
        unsigned long sc;
        if (k == 0) {
            sc = CHAR_MAX;
            printf("1. processing CHAR_MAX \n");
        } else if (k == 1) {
            sc = UCHAR_MAX;
            printf("processing UCHAR_MAX \n");
        } else if (k == 2) {
            sc = ULONG_MAX;
            printf("processing ULONG_MAX \n");
        } else if (k == 3) {
            sc = LONG_MAX;
            printf("processing LONG_MAX \n");
        } else if (k == 4) {
            sc = CHAR_MIN;
            printf("processing CHAR_MIN \n");
        } else if (k == 5) {
            sc = LONG_MIN;
            printf("processing LONG_MIN \n");
        }
        printf("%lu\n", sc);
        unsigned int si = sc;
        printf("%u\n", si);
        unsigned short int i = si;
        printf("%hu\n", i);
        unsigned char l = i;
        printf("%c\n", l);
    }

    for (int k = 0; k < 6; k++) {
        signed long sc;
        if (k == 0) {
            sc = CHAR_MAX;
            printf("1. processing CHAR_MAX \n");
        } else if (k == 1) {
            sc = UCHAR_MAX;
            printf("processing UCHAR_MAX \n");
        } else if (k == 2) {
            sc = ULONG_MAX;
            printf("processing ULONG_MAX \n");
        } else if (k == 3) {
            sc = LONG_MAX;
            printf("processing LONG_MAX \n");
        } else if (k == 4) {
            sc = CHAR_MIN;
            printf("processing CHAR_MIN \n");
        } else if (k == 5) {
            sc = LONG_MIN;
            printf("processing LONG_MIN \n");
        }
        printf("%ld\n", sc);
        signed int si = sc;
        printf("%d\n", si);
        signed short int i = si;
        printf("%hd\n", i);
        signed char l = i;
        printf("%c\n", l);
    }

    printf("Processing MAX+1: \n");

    signed int maxis = INT_MAX;
    maxis += 1;
    printf("%s, %d\n", "INT_MAX+1", maxis);

    unsigned int maxisu = UINT_MAX;
    maxisu += 1;
    printf("%s, %d\n", "UNSIGNED_INT_MAX+1", maxisu);

    printf("Processing MAX-1: \n");

    signed int min = INT_MIN;
    min -= 1;
    printf("%s, %d\n", "SIGNED_INT_MIN+1", min);

    unsigned int minu = 0;
    minu -= 1;
    printf("%s, %d\n", "UNSIGNED_INT_MIN+1", minu);
}