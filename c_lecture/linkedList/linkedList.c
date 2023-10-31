#include "linkedList.h"

void init_list(struct LinkedList * list){
    list->size = 0;
    list->back = NULL;
    list->front = NULL;
}

void push_back(struct LinkedList * list, int value){
    struct Node * node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = value;

    // If there are no elements in the list, then assign front and back to this node
    if(list->size == 0){
        list->back = node;
        list->front = node;
        node->prev = NULL;
    }else{
        list->back->next = node;
        node->prev = list->back;
        list->back = node;
    }

    list->size++;
}

void push_front(struct LinkedList * list, int value){
    struct Node * node = malloc(sizeof(struct Node));
    node->prev = NULL;
    node->data = value;

    // If there are no elements in the list, then assign front and back to this node
    if(list->size == 0){
        list->back = node;
        list->front = node;
        node->next = NULL;
    }else{
        list->front->prev = node;
        node->next = list->front;
        list->front = node;
    }

    list->size++;
}

int pop_back(struct LinkedList * list){
    if(list->size == 0){
        printf("ERROR: No elements on list to remove!\n");
        return 0;
    }

    struct Node * endNode = list->back;
    list->back = endNode->prev;
    if(list->back != NULL){
        list->back->next = NULL;
    }
    
    int retVal = endNode->data;
    free(endNode);
    list->size--;
    return retVal;
}


int pop_front(struct LinkedList * list){
    if(list->size == 0){
        printf("ERROR: No elements on list to remove!\n");
        return 0;
    }

    struct Node * frontNode = list->front;
    list->front = frontNode->next;    
    if(list->front != NULL){
        list->front->prev = NULL;
    }
    

    int retVal = frontNode->data;
    free(frontNode);
    list->size--;
    return retVal;
}

void print_values(struct LinkedList * list){
    struct Node * ptr = list->front;
    while (ptr != NULL)
    {
        printf("%i ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}