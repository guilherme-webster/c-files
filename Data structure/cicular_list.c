#include <stdio.h>
#include <stdlib.h> 

typedef struct node{

    int d;
    struct node* next;

}node;

typedef struct noden{

    char d;
    struct noden* next;
    struct noden* prev;

}noden;

typedef struct List{


    struct node* head;
    struct node* tail;

}list;

typedef struct Listn{


    struct noden* head;
    struct noden* tail;

}listn;

list* create(){
    list* L = malloc(sizeof(list));
    L->head = NULL;
    L->tail = NULL;
    return L;
}

listn* createn(){
    listn* L = malloc(sizeof(listn));
    L->head = NULL;
    L->tail = NULL;
    return L;
}

int inject(list* L, int n){ // insere um elemento no comeco da lista
    node* p = malloc(sizeof(node));
    if (!p)
        return 0;
    p->d = n;

    p->next = L->head;
    L->head = p;
    if(!L->tail)
        L->tail = p;
    L->tail->next = L->head;
    return 1;
}

int rem(list* L, int m){ // remove o m-ésimo nó a partir do primeiro enquanto tiverem dois ou mais elementos na lista
    int n = 1;
    node* p = L->head;
    while(p->next != p){
        for(int i = 0; i < m; i ++){
            if(p->next != p){
                p->next = p->next->next;
                n++;
            }
        }
        p = p->next;
    }
    return n;
}

void printl(listn* L){ // printa a lista
    noden* p = L->head;
    while (p != L->tail){
        printf("%c ", p->d);
        p = p->next;
    }
    printf("%c ", p->d);
    printf("\n");
}

/*int push(list* L, int n){
    node* p = malloc(sizeof(node));
    if (!p)
        return 0;

    p->d = n;
    p->next = NULL;

    if (L->head == NULL){
        L->head = p;
        return 1;
    }

    node* q = malloc(sizeof(node));
    q = L->head;
    while (q->next){
        q = q->next;
    }
    q->next = p;
    return 1;
}*/

/*int insert_at_k(list *L, int n, int k){
    node* p = malloc(sizeof(node));

    if (!p)
        return 0;

    p->d = n;

    if (L->head == NULL){
        p->next = NULL;
        L->head = p;
    }
    node* q = malloc(sizeof(node));
    q = L->head;

    for (int i = 0; i < k - 1; i++){
        q = q->next;
    }

    p->next = q->next;
    q->next = p;
    return 1;
}*/

int injectn(listn* L, char c){
    noden* p = malloc(sizeof(noden));
    if (!p)
        return 0;
    p->d = c;

    p->next = L->head;
    p->prev = L->tail;
    L->head = p;
    if(!L->tail)
        L->tail = p;
    L->tail->next = L->head;
    return 1;
}

noden* func(noden* head, int n){ // checa se a lista é do tipo 0...01..1 com n 0's e n 1's
    noden* q = head;
    while(q){
        noden* p = q;
        if(p->d == '0'){
            for(int i = 0; i < n; i++){
                if(p->d != '0')
                    return NULL;
                p = p->next;
            }
            for(int i = 0; i < n; i++){
                if(p->d != '1')
                    return NULL;
                p = p->next;
            }
            return q;
        }
        q = q->next;
    }
}

int main(){
    list* L = create();
    /*injectn(L, '1');
    injectn(L, '1');
    injectn(L, '0');
    injectn(L, 'a');
    injectn(L, 'a');*/
    inject(L, 4);
    inject(L, 3);
    inject(L, 2);
    inject(L, 1);
    printf("%d", rem(L, 2));
    /*noden* head = L->head;
    noden* node = func(head, 2);
    if(node)
        printf("%d\n", 1);
    else
        printf("%d\n", 0);*/
}
