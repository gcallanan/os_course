/**
 * A simple pointer demo
 * 
 * In a linux terminal compile with: gcc -o pointers.out pointers.c
 * And then run with: ./pointers.out
 */

#include <stdio.h>
int main() {
    int i = 10;
    printf("The value of i is: %i\n", i);
    printf("The address of i is: %p\n\n", &i);

    int * ptr = &i; 
    // The value of ptr should be the address of i
    printf("The value of ptr is: %p\n", ptr);
    // Lets dereference the pointer (get the value it points to)
    printf("The value at the address ptr points to is: %i\n", *ptr);



    return 0;
}

