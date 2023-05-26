#ifndef LIST_H
#define LIST_H

typedef struct node {
    char data;
    struct node* next;
    struct node* before;
    int position;
} node;

typedef struct list {
    node* first;
    node* last;
    int size;
} list;

list* startList ();
void addFirstItem (list*, char);
void addItem (list*, char);
void freeList (list*);

#endif