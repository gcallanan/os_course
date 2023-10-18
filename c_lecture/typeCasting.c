/**
 * A program dmonstrating simple type casting in C
 * 
 * In a linux terminal compile with: gcc -o typeCasting.out typeCasting.c
 * And then run with: ./typeCasting.out
 */

#include <stdio.h>
int main() {
    // This line is a comment
    int i = 10;
    double d = 5.5;

    // Primitive types are implicitly cast in a way that avoids data loss. 
    // Here i is cast to a double
    double sumDouble = d + i; // We expect result to be 15.5

    // We can explicitly cast types in cases where data can be lost.
    // “(int) d” casts d to an integer
    int sumInt = (int) d + i; // We expect the result to be 15

    // https://www.geeksforgeeks.org/printf-in-c/
    printf("Double Sum: %f\n", sumDouble);
    printf("Integer Sum: %i\n", sumInt);

    return 0;
}
