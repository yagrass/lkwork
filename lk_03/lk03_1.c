// #include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

#define LL1     XOR(merge->addr, left)
#define LL2     merge    
#define RR1     XOR(merge->addr, right)
#define RR2     merge

#define showAddr(addr)  ((unsigned long int)addr & 0xFFFFF)

void insert_node(list **l, int d) {
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
        printf("\t");
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
        printf("*->addr:%lx,", showAddr((*l)->addr));
    }
    *l = tmp;
    printf("\t [%d,%lx]@%lx\n", d, showAddr((*l)->addr), showAddr(*l));    
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l);
        free(l);
        l = next;
    }
}

void dList(list *l, int dloop, char *msg)
{
    printf("<%d> %s:", dloop, msg);
 
    if (!l) {
        printf("\n");
        return;
    }
    list *next = l->addr;
    while (l) {
        list *nextnext;
        printf("[%d,%lx]@%lx,", l->data,
        (unsigned long int)l->addr & 0xFFFF,
        (unsigned long int)l & 0xFFFF );        
        if (next)
        {
            nextnext = XOR(next->addr, l);
        } 
        l = next;
        next = nextnext;
    }   
    printf("\n"); 
}

void printList(list *l) {
    if (!l)
        return;
    list *next = l->addr;
    while (l) {
        list *nextnext;
        printf("\t[%d,%lx]@%lx", l->data, showAddr(l->addr), showAddr(l));
        if (next)
        {
            printf(",next->addr:%lx->", showAddr(next->addr));
            nextnext = XOR(next->addr, l);
            printf("%lx,\n", showAddr(nextnext));
        } else {printf("\n");}
        l = next;
        next = nextnext;
    }    
}

list *sort(list *start, int dloop)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    dList(left, dloop, "B_left>");
    dList(right, dloop, "B_right>");

    left = sort(left, dloop+1);
    right = sort(right, dloop+1);

    dList(left, dloop, "M_left>");
    dList(right, dloop, "M_right>");

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            printf("##### L block #####\n");
            if (next) {
                next->addr = XOR(left, next->addr);
                // dList(next->addr, dloop, "\tl_Naddr>");    
            }
            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = LL1;
                left->addr = LL2;
                merge = left;
            }
            left = next;
            dList(left, dloop, "\tl_left>");
            dList(right, dloop, "\tl_right>");
            dList(start, dloop, "\tl_start>");
            dList(merge, dloop, "\tl_merge>");
        } else {
            list *next = right->addr;
            printf("##### G block #####\n");
            if (next) {
                next->addr = XOR(right, next->addr);
                // dList(next->addr, dloop, "\tg_Naddr>");
            }
            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = RR1;
                right->addr = RR2;
                merge = right;
            }
            right = next;
            dList(left, dloop, "\tg_left>");
            dList(right, dloop, "\tg_right>");
            dList(start, dloop, "\tg_start>");
            dList(merge, dloop, "\tg_merge>");
        }
    }

    return start;
}

int main()
{
    list *xorList = (list *)NULL;
    insert_node(&xorList, 2);
    insert_node(&xorList, 1);
    insert_node(&xorList, 7);
    insert_node(&xorList, 0);
    insert_node(&xorList, 3);
    insert_node(&xorList, 1);
    insert_node(&xorList, 4);

    printList(xorList);

    printf("\n\n sort start!\n\n");

    xorList = sort(xorList, 0);

    printList(xorList);

    return 0;
}
