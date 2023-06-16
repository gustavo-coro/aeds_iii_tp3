#include "../include/lista.h"

// aloca para a memoria uma lista vazia
list* startList () {
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    return l;
}

// adiciona o primeiro item da lista
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

// adiciona demais itens na lista
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

// desaloca a lista e seus componentes
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