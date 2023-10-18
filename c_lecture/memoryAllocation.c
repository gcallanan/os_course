/**
 * A demo showing the difference between passing by value and by reference
 * 
 * In a linux terminal compile with: gcc -o memoryAllocation.out memoryAllocation.c
 * And then run with: ./memoryAllocation.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int numElements = rand() % 10 + 3;
    int * ptr = (int*) malloc(numElements * sizeof(int));
    printf("Allocated %i elements. Starting address: %p\n", numElements ,ptr);

    for (int i = 0; i < numElements; i++)
    {
        ptr[i] = i*2+1;
        printf("Value at offset %i: %i %p\n", i, ptr[i], ptr + i);
    }
    

    free(ptr);
    return 0;
}