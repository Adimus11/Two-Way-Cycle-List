#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct CycleList{
    int value;
    struct CycleList *prev;
    struct CycleList *next;
};

struct CycleList *newList(int value){
    struct CycleList *list = malloc(sizeof(struct CycleList));

    list->value = value;
    list->next = list;
    list->prev = list;

    return list;
}

void addToList(struct CycleList *l, int value){
    if(l == NULL){
        printf("List not initialized or empty, pleas first use newList()...\n");
        return ;
    }

    struct CycleList *new = malloc(sizeof(struct CycleList));
    new->value = value;
    new->next = l;
    new->prev = l->prev;

    l->prev->next = new;
    l->prev = new;
}

void removeElementAt(struct CycleList **l, int position){
    struct CycleList *begin = *l;
    struct CycleList *temp = *l;
    int iterator = 0;
    if(*l == NULL){
        printf("List is already empty...\n");
        return ;
    }

    if(begin->next == begin->prev){
        free(*l);
        *l = NULL;
        return ;
    }

    while(iterator < position){
        iterator++;
        temp = temp->next;
    }


    if(temp == begin){
        temp = (*l)->next;
        temp->prev = temp->prev->prev;
        temp->prev->next = temp;

        free(*l);
        *l = temp;

        return ;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);
}

int getElementAt(struct CycleList *l, int position){
    int iterator = 0;

    while(iterator < position){
        l = l->next;
        iterator++;
    }

    return l->value;
}

void printListNormal(struct CycleList *l){
    struct CycleList *first = l;

    printf("[ ");

    while(l->next != first){
        printf("%d, ", l->value);
        l = l->next;
    }

    printf("%d ]\n", l->value);
}

void printListReverse(struct CycleList *l){
    l = l->prev;
    struct CycleList *last = l;

    printf("[ ");

    while(l->prev != last){
        printf("%d, ", l->value);
        l = l->prev;
    }

    printf("%d ]\n", l->value);
}

struct CycleList *megre(struct CycleList **a, struct CycleList **b){
    struct CycleList *new = *a;
    (*a)->prev->next = (*b);
    (*b)->prev->next = (*a);

    (*a) = NULL;
    (*b) = NULL;

    return new;
}

int main(){
    srand(time(NULL));

    struct CycleList *list = newList(25);
    addToList(list, 723);
    addToList(list, 123);
    addToList(list, 223);
    addToList(list, 235);
    addToList(list, 623);

    printListNormal(list);
    printListReverse(list);
    printf("Element: %d\n", getElementAt(list, 0));
    printf("Element: %d\n", getElementAt(list, 34));
    printf("Element: %d\n", getElementAt(list, 3));

    removeElementAt(&list, 0);
    printListNormal(list);

    removeElementAt(&list, 3);
    printListNormal(list);

    removeElementAt(&list, 15);
    printListNormal(list);

    struct CycleList *list2 = newList(1);
    addToList(list2, 2);
    addToList(list2, 3);
    addToList(list2, 4);
    addToList(list2, 5);
    addToList(list2, 6);

    printListNormal(list2);

    struct CycleList *listMerged = megre(&list, &list2);
    printListNormal(listMerged);

    struct CycleList *bigList = newList(rand()%1001);
    int i;
    for(i = 0; i < 999; i++){
        addToList(bigList, rand()%1001);
    }

    double start, end;
    int selected;

    selected = getElementAt(bigList, 512);
    struct timeval  tv1, tv2;

    gettimeofday(&tv1, NULL);
    selected = getElementAt(bigList, 512);
    gettimeofday(&tv2, NULL);

    printf ("Selecting the same element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    gettimeofday(&tv1, NULL);
    selected = getElementAt(bigList, rand()%1000);
    gettimeofday(&tv2, NULL);

    printf ("Selecting random element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}