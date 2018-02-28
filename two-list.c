#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct CycleList{
    int size;
    struct Node *start;
};

struct Node{
    int value;
    struct Node *prev;
    struct Node *next;
};

struct CycleList *newList(){
    struct CycleList *list = malloc(sizeof(struct CycleList));

    list->size = 0;
    list->start = NULL;

    return list;
}

void addToList(struct CycleList *l, int value){
    if(l->size == 0){
        struct Node *temp = malloc(sizeof(struct Node));

        temp->prev = temp;
        temp->next = temp;
        temp->value = value;

        l->start = temp;
        l->size++;

        return ;
    }

    struct Node *new = malloc(sizeof(struct Node));
    new->value = value;
    new->next = l->start;
    new->prev = l->start->prev;

    l->start->prev->next = new;
    l->start->prev = new;
    l->size++;
}

void removeElementAt(struct CycleList *l, int position){
    if(position >= l->size){
        printf("Such element does not exists...\n");
        return ;
    }

    int iterator;

    if(position == 0){
        struct Node *temp = l->start;
        struct Node *help = l->start->next;
        l->size--;

        
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        l->start = temp->next;

        free(temp);

        return ;
    }

    if(position < (l->size/2)){
        //This side of list is faster
        iterator = 0;
        struct Node *temp = l->start;

        while(iterator != position){
            iterator++;
            temp = temp->next;
        }

        l->size--;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        free(temp);

    }
    else{
        //This time, this side of list is faster xD
        iterator = l->size - 1;
        struct Node *temp = l->start->prev;

        while(iterator != position){
            iterator--;
            temp = temp->prev;
        }

        l->size--;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        free(temp);

    }
}

int getElementAt(struct CycleList *l, int position){
    int iterator;
    struct Node *temp;

    if(position >= l->size){
        printf("There is no such a element, returning 0...\n");
        return 0;
    }

    if(position < (l->size/2)){
        iterator = 0;
        temp = l->start;

        while(iterator != position){
            iterator++;
            temp = temp->next;
        }
    }
    else{
        iterator = l->size - 1;
        temp = l->start->prev;

        while(iterator != position){
            iterator--;
            temp = temp->prev;
        }

    }

    return temp->value;
}

int getElementPosition(struct CycleList *l, int element){
    if(l->size == 0){
        printf("List is empty...\n");
        return -1;
    }

    struct Node *temp = l->start;
    int iterator = 0;

    while(temp != NULL){
        if(temp->value == element){
            return iterator;
        }
        temp = temp->next;
        iterator++;
    }

    return -1;
}

void printListNormal(struct CycleList *l){
    struct Node *temp = l->start;

    printf("[ ");

    int iterator = 0;

    while(iterator < l->size){
        printf("%d, ", temp->value);
        temp = temp->next;
        iterator++;
    }

    printf(" ]\n");
}

void printListReverse(struct CycleList *l){
    struct Node *temp = l->start->prev;

    printf("[ ");

    int iterator = 0;

    while(iterator < l->size){
        printf("%d, ", temp->value);
        temp = temp->prev;
        iterator++;
    }

    printf(" ]\n");
}

struct CycleList *megre(struct CycleList *a, struct CycleList *b){
    struct CycleList *new = newList();

    struct Node *temp = a->start;
    int iterator = 0;

    while(iterator < a->size){
        addToList(new, temp->value);
        temp = temp->next;
        iterator++;
    }

    temp = b->start;
    iterator = 0;

    while(iterator < b->size){
        addToList(new, temp->value);
        temp = temp->next;
        iterator++;
    }
    
    
    return new;
}

int main(){
    srand(time(NULL));

    struct CycleList *list = newList();

    printf("Add test\n");
    addToList(list, 723);
    addToList(list, 123);
    addToList(list, 223);
    addToList(list, 235);
    addToList(list, 623);

    printf("Print test\n");
    printListNormal(list);
    printListReverse(list);

    printf("Get element at t test\n");
    printf("Element: %d\n", getElementAt(list, 0));
    printf("Element: %d\n", getElementAt(list, 34));
    printf("Element: %d\n", getElementAt(list, 3));

    printf("Removal test\n");
    removeElementAt(list, 0);
    printListNormal(list);

    removeElementAt(list, 3);
    printListNormal(list);

    removeElementAt(list, 15);
    printListNormal(list);

    struct CycleList *list2 = newList();
    addToList(list2, 2);
    addToList(list2, 3);
    addToList(list2, 4);
    addToList(list2, 5);
    addToList(list2, 6);

    printListNormal(list2);

    struct CycleList *listMerged = megre(list, list2);
    printListNormal(listMerged);

    struct CycleList *bigList = newList();
    int i;
    for(i = 0; i < 1000; i++){
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