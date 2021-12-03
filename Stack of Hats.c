#include<stdio.h>
#include <stdlib.h>

typedef struct node *list;
struct node{
    int size;
    int num;
    list next;
    list next2;
};
int main()
{
    int n, i;
    scanf("%d", &n);
    list hat = (list)malloc(sizeof(struct node));
    hat->next = NULL;
    list people = (list)malloc(sizeof(struct node));
    people->next = NULL;
    list stack = (list)malloc(sizeof(struct node));
    stack->next2 = NULL;
    for(i = 0; i < n; i++)
    {
        list t1 = hat;
        list temp = (list)malloc(sizeof(struct node));
        scanf("%d", &temp->size);
        temp->next2 = stack->next2;
        stack->next2 = temp;
        while(t1->next != NULL&&temp->size > t1->next->size)
        {
            t1 = t1->next;
        }
        temp->next = t1->next;
        t1->next = temp;
    }
    for(i = 0; i < n; i++)
    {
        list t2 = people;
        list temp = (list)malloc(sizeof(struct node));
        temp->num = i+1;
        scanf("%d", &temp->size);
        while(t2->next != NULL&&temp->size > t2->next->size)
        {
            t2 = t2->next;
        }
        temp->next = t2->next;
        t2->next = temp;
    }
    list t1 = hat->next;
    list t2 = people->next;
    for(i = 0; i < n; i++)
    {
        t1->num = t2->num;
        t1 = t1->next;
        t2 = t2->next;
    }
    int flag = 1;
    while(stack->next2 != NULL)
    {
        printf("%s%d",flag?"":" ",stack->next2->num);
        flag = 0;
        stack->next2 = stack->next2->next2;
    }
    return 0;
}

