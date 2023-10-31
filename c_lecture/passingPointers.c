/**
 * A demo showing the difference between passing pointers to a variable vs passing the actual variable
 * 
 * In a linux terminal compile with: gcc -o passingPointers.out passingPointers.c
 * And then run with: ./passingPointers.out
 */

#include <stdio.h>
void simpleFunction(int val, int * ref){
    printf("2. val address: %p, ref value: %p\n", &val, ref);
    printf("3. val: %i, ref: %i\n\n\n", val, *ref);
    val = val + 1;
    *ref = *ref + 1;
}

int main() {
    int a = 10;
    int b = 20;
    printf("0. a address: %p, b address: %p\n", &a, &b);
    printf("1. a: %i, b: %i\n\n\n", a, b);
    simpleFunction(a,&b);
    printf("4. a: %i, b: %i\n", a, b);
    return 0;
}