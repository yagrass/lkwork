// #include <stdbool.h>
// #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define P2P

#define AA (*link)->data < newt->data
#define BB link = &(*link)->next
#define cons(x, y) (struct node[]){{x, y}}

#include <stddef.h>
struct node {
    int data;
    struct node *next;
} *head;

// struct node *head = NULL;

#ifndef P2P
void insert(struct node *newt) {
    struct node *node = head, *prev = NULL;
    while (node != NULL && node->data < newt->data) {
        prev = node;
        node = node->next;
    }
    newt->next = node;
    if (prev == NULL)
        head = newt;
    else
        prev->next = newt;
}
#else
void insert(struct node *newt)
{
    struct node **link = &head;
    while (*link && AA)
        BB;
    newt->next = *link;
    *link = newt;
}
#endif

void printList(struct node *nd)
{
    for(; nd; nd=nd->next)
      printf("%d,", nd->data);
    printf("\n");
}

struct node *sort(struct node *start, int dloop) {
    if (!start || !start->next)
        return start;
    struct node *left = start;
    struct node *right = left->next;
    /*LL0;  */ left->next = NULL;

    left = sort(left, dloop+1);
    right = sort(right, dloop+1);

    for (struct node *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                /*LL1;    */ start = merge = left;
            } else {
                /*LL2;    */ merge->next = left;
                merge = merge->next;
            }
            /*LL3;    */ left = left->next;
        } else {
            if (!merge) {
                /*LL4;    */ start = merge = right;
            } else {
                /*LL5;    */ merge->next = right;
                merge = merge->next;
            }
            /* LL6;    */ right = right->next;
        }
    }
    return start;
}

int main()
{
    head = cons(4, cons(1, cons(3, cons(0, (cons(7, cons(1, cons(2, NULL))))))));

    struct node Node_5 = {5, NULL};
    struct node Node_55 = {55, NULL};

    printList(head);

    head = sort(head, 0);

    printList(head);

    // insert 5 
    insert(&Node_5);
    printList(head);

    // insert 55
    insert(&Node_55);
    printList(head);

    return 0;
}
