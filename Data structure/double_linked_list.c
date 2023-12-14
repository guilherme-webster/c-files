#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int d;
    struct node* next;
    struct node* prev;
}node;

node* create_list(){
    node** L = malloc(sizeof(node*));
    *L = NULL;
    return *L;
}

node* last_node(node** L){
    node* aux = *L;
    while(aux->next)
        aux = aux->next;
    return aux;
}

int inject(node **L, int k){
    node* p = malloc(sizeof(node));

    if (!p)
        return 0;

    p->d = k;
    p->next = *L;
    p->prev = NULL;
    if (*L)
        (*L)->prev = p;
    *L = p;
    return 1;
}

int push(node **L, int k){
    node* p = malloc(sizeof(node));

    if (!p)
        return 0;

    p->d = k;
    p->next = NULL;

    if (*L == NULL){
        *L = p;
        p->prev = NULL;
        return 1;
    }

    node* q = malloc(sizeof(node));
    q = *L;
    while (q->next){
        q = q->next;
    }
    q->next = p;
    p->prev = q;
    return 1;
}
// k is the idx, be careful to acess a valid idx
int insert_at_k(node **L, int n, int k){
    node* p = malloc(sizeof(node));

    if (!p)
        return 0;

    p->d = n;

    if (*L == NULL){
        p->next = NULL;
        p->prev = NULL;
        *L = p;
    }
    node* q = malloc(sizeof(node));
    q = *L;

    for (int i = 0; i < k - 1; i++){
        q = q->next;
    }

    p->next = q->next;
    q->next->prev = p;
    p->prev = q;
    q->next = p;
    return 1;
}

void printl(node **L){
    node *p = malloc(sizeof(node));
    p = *L;
    while (p){
        printf("%d ", p->d);
        p = p->next;
    }
    printf("\n");
}

void printl_back(node **L){
    node* last = last_node(L);
    while (last){
        printf("%d ", last->d);
        last = last->prev;
    }
    printf("\n");
}

void copy_list(node **a, node **b){
    node* aux = *a;
    while (aux){
        inject(b, aux->d);
        aux = aux->next;
    }
}

int insert_o(node** L, int n){
    node *q, *p = malloc(sizeof(node));
    if (!p)
        return 0;
    p->d = n;

    if (*L == NULL){ // if the list is empty, p will be the first element
        p->next = NULL;
        p->prev = NULL;
        *L = p;
        return 1;
    }

    if (p->d < (*L)->d){ // if p is less than the first element of the list, p will be the new first element
        p->next = *L;
        (*L)->prev = p;
        *L = p;
        return 1;
    } else {
        q = *L;
        while(q->next && p->d > q->next->d){
            q = q->next;
        }
        if (q->next) {
            p->next = q->next;
            q->next->prev = p;
            p->prev = q;
        } else {
            p->next = NULL;
            p->prev = q;
        }
        q->next = p;
        return 1;
    }
}

int rmv_fr_beg(node **L){
    if (*L == NULL)
        return 1;

    node *p = *L;
    *L = (*L)->next;
    if (*L)
        (*L)->prev = NULL;
    free(p);
    return 1;
}

int rmv_fr_end(node **L){
    if (*L == NULL)
        return 1;

    node *p = *L;
    if(p->next == NULL){
        free(*L);
        *L = NULL;
        return 1;
    } else {
    while(p->next->next)
        p = p->next;

    free(p->next);
    p->next = NULL;
    return 1;
    }
}

node* search(node **L, int n){
    node *p, *q = NULL;
    p = *L;
    while (p && p->d != n)
        p = p->next;
    if (p)
        q = p;
    return q;
}

int main(){
    node* L1 = create_list();
    node* L2 = create_list();
    node* L3 = create_list();
    node *searched = NULL;

    push(&L2,3);
    inject(&L2,6);
    inject(&L2,25);

    inject(&L3,42);
    inject(&L3,51);
    
    push(&L1, 39);
    insert_o(&L1, 1);
    insert_o(&L1, 101);
    printl(&L1);
    //rmv_fr_beg(&L1);
    printl(&L2);
    //rmv_fr_end(&L1);
    printl(&L3);
    /*searched = search(&L1, 1000);
    if (searched)
        printf("Found: %d\n", searched->d);
    else
        printf("Not found!\n");*/
    printf("\n");
    copy_list(&L2, &L1);
    copy_list(&L3, &L1);
    printl(&L1);
    printl_back(&L1);
}