/**
 * A demo showing the difference between passing by value and by reference
 * 
 * In a linux terminal compile with: gcc -o list.out main.c linkedList.c
 * And then run with: ./list.out
 */

#include <stdio.h>
#include "linkedList.h"

int main() {
    struct LinkedList list;
    init_list(&list);
    push_back(&list, 13);
    push_back(&list, 7);
    push_back(&list, 0);
    push_front(&list, 42);
    print_values(&list);
    return 0;
}