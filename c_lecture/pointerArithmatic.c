/**
 * A demo demonstrating pointer arithmatic
 * 
 * In a linux terminal compile with: gcc -o pointerArithmatic.out pointerArithmatic.c
 * And then run with: ./pointerArithmatic.out
 */

#include <stdio.h>
int main() {
    int a[5] = {0,1,2,3,4};
    int * ptr = a;
    
    for (size_t i = 0; i < 5; i++)
    {
        printf("Address: %p, Value ptr: %i, Value array: %i\n", ptr + i, *(ptr + i), a[i]);
    }
    
}