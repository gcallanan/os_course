#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct Node{
    struct Node * prev;
    struct Node * next;
    int data;
};

struct LinkedList{
  struct Node * front;
  struct Node * back;
  int size;  
};

void init_list(struct LinkedList * list);
void push_back(struct LinkedList * list, int value);
void push_front(struct LinkedList * list, int value);
int pop_back(struct LinkedList * list);
int pop_front(struct LinkedList * list);
void print_values(struct LinkedList * list);

#endif