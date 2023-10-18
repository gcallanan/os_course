/**
 * A simple array demo
 * 
 * In a linux terminal compile with: gcc -o simpleArray.out simpleArray.c
 * And then run with: ./simpleArray.out
 */

#include <stdio.h>
int main() {
    int a[10];
    for(int i = 0; i < 5; i++){
        a[i] = i;
        printf("Index %i, Value %i\n", i, a[i]);
    }
}

