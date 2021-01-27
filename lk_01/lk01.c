#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TestStart 1

typedef struct __list {
    int data;
    struct __list *next;
} list;

#define cons(x, y) (struct __list[]){{x, y}}

#define LL0     left->next = NULL
#define LL1     start = merge = left
#define LL2     merge->next = left
#define LL3     left = left->next
#define LL4     start = merge = right
#define LL5     merge->next = right
#define LL6     right = right->next

#ifdef TestStart

void dList(list *lst, int dloop, char *msg)
{
  printf("<%d> %s:", dloop, msg);
  for(; lst; lst = lst->next)
    printf("%d@%lx,", lst->data,(unsigned long int)lst & 0xFFFFF );
  printf("\n");  
}

list *sort(list *start, int dloop) {
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    /*LL0;  */ left->next = NULL;

    dList(left, dloop, "B_left>");
    dList(right, dloop, "B_right>");

    left = sort(left, dloop+1);
    right = sort(right, dloop+1);
    
    dList(left, dloop, "M_left>");
    dList(right, dloop, "M_right>");

    for (list *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                /*LL1;    */ start = merge = left;
            } else {
                /*LL2;    */ merge->next = left;
                merge = merge->next;
            }
            /*LL3;    */ left = left->next;
            dList(left, dloop, "\tl_left>");
            dList(right, dloop, "\tl_right>");
            dList(start, dloop, "\tl_start>");
            dList(merge, dloop, "\tl_merge>");
            dList(merge->next, dloop, "\tl_mNext>");
        } else {
            if (!merge) {
                /*LL4;    */ start = merge = right;
            } else {
                /*LL5;    */ merge->next = right;
                merge = merge->next;
            }
            /* LL6;    */ right = right->next;
            dList(left, dloop, "\tg_left>");
            dList(right, dloop, "\tg_right>");
            dList(start, dloop, "\tg_start>");
            dList(merge, dloop, "\tg_merge>");
            dList(merge->next, dloop, "\tl_mNext>");          
        }
    }
    return start;
}
#endif
void printList(list *lst)
{
  for(; lst; lst = lst->next)
    printf("%d,", lst->data);
  printf("\n");  
}

void main(void)
{
  list *linkList = cons(86, cons(45, cons(70, cons(50, (cons(30, cons(100, NULL)))))));
  printList(linkList);

#ifdef TestStart
  linkList = sort(linkList, 0);
  printList(linkList);
#endif
}