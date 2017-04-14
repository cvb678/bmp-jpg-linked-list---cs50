#include <stdio.h>

typedef struct node {
    struct node * next;
    struct node * prev;
    int value;
} node_t;

typedef struct linkedList {
    int length;
    struct node * first;
    struct node * last;
} linkedList_t;

void initializeList (linkedList_t * llp) {
    llp->length = 0;
    llp->first = NULL;
    llp->last = NULL;
    printf("List initialized!\n");
}

void initializeNode (node_t * np, int val) {
    np->next = NULL;
    np->prev = NULL;
    np->value = val;
}

void addNode (linkedList_t * llp, node_t * np) {

    if(llp->length == 0 && llp->first == NULL) {
        llp->first = np;
        llp->last = np;
    }
    else {
        np->prev = llp->last;
        llp->last->next = np;
        llp->last = np;
    }

    llp->length++;
}

void delNode (linkedList_t * llp, int index) {
    if (index >= llp->length)
    {
        printf("Index out of bounds!");
        return;
    }

    node_t * curr = llp->first;

    int i;
    for(i=0; i<index; i++) {
        curr = curr->next;
    }

    node_t * toDelete = curr;

    curr = toDelete->prev;
    curr->next = toDelete->next;

    curr = toDelete->next;
    curr->prev = toDelete->prev;

    free(toDelete);
    llp->length--;

}

int main(void) {

    linkedList_t myList;
    initializeList(&myList);

    char d;
    int delIndex, counter = 0;

    while(1) {
        printf("Add press d\n");
        printf("Remove press r\n");
        printf("Print press p\n");
        printf("Print backwards press b\n");
        printf("Quit press q\n");

        scanf("\n%c", &d);

        if(d == 'q') {
            //free the list!
            if(myList.length > 0) {
                node_t * curr = myList.first;
                node_t * toDel = myList.first;
                int i;

                for(i=0; i<myList.length; i++) {
                    if(curr->next != NULL) {
                        curr=curr->next;
                        free(toDel);
                        toDel=curr;
                    }
                }
                free(curr);
            }
            return 0;
        }
        else if(d== 'd') {
            node_t * np = malloc(sizeof(node_t));
            initializeNode(np, counter++);
            addNode(&myList, np);
        }
        else if(d == 'p') {
            int i;
            node_t * curr = myList.first;
            for(i = 0; i < myList.length; i++) {
                printf("Node index: %i, has value %i \n", i, curr->value);
                curr = curr->next;
            }
        }
        else if(d == 'b') {
            int i;
            node_t * curr = myList.last;
            for(i = myList.length; i > 0; i--) {
                printf("Node index: %i, has value %i \n", i-1, curr->value);
                curr = curr->prev;
            }
        }
        else if(d == 'r') {
            printf("What index to remove? : ");
            scanf("\n%i", &delIndex);
            delNode(&myList, delIndex);
        }

    }

    return 0;
}
