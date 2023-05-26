#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

list* startList () {
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    return l;
}

void addFirstItem (list* l, char data) {
    node* f = (node*) malloc(sizeof(node));
    f->data = data;
    f->next = f;
    f->before = f;
    f->position = 1;
    l->last = f;
    l->first = f;
    l->size = 1;
}

void addItem (list* l, char data) {
    node* f = (node*) malloc(sizeof(node));
    f->data = data;
    f->next = l->first;
    f->before = l->last;
    f->position = f->before->position + 1;
    l->last->next = f;
    l->first->before = f;
    l->last = f;
    l->size ++;
}

void freeList (list* l) {
    for (int i = 0; i < l->size-1; i++) {
        node* temp;
        temp = l->first;
        l->first = temp->next;
        free(temp);
    }
    free(l->first);
    free(l);
}