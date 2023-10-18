#include <stdio.h>
#include "multiplyByX.h"

/**
 * Perform preprocessing only: gcc -E main.c multiplyByX.c
 * Perform preprocessing and compilation: gcc -c main.c multiplyByX.c
 * link files after they have been compiled: gcc -o executable.out main.o multiplyByX.o
 */

int main() {
    int i = 10;
    int result = multiplyByTwo(i);
    printf("Result: %i\n", result);
    return 0;
}
