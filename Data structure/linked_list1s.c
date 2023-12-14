#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int d;
    int visited;
    struct node* next;

}node;

typedef struct nodec{

    char c;
    struct nodec* next;

}nodec;

node* create_list(){
    node** L = malloc(sizeof(node*));
    *L = NULL;
    return *L;
}

nodec* create_listc(){
    nodec** L = malloc(sizeof(nodec*));
    *L = NULL;
    return *L;
}

int inject(node **L, int k){
    node* p = malloc(sizeof(node));

    if (!p)
        return 0;

    p->d = k;
    p->next = *L;
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
        return 1;
    }

    
    node *q = *L;
    while (q->next){
        q = q->next;
    }
    q->next = p;
    return 1;
}

int pushl(nodec **L, char c){
    nodec* p = malloc(sizeof(nodec));

    if (!p)
        return 0;

    p->c = c;
    p->next = NULL;

    if (*L == NULL){
        *L = p;
        return 1;
    }

    
    nodec *q = *L;
    while (q->next){
        q = q->next;
    }
    q->next = p;
    return 1;
}

// k is the idx, be careful to acess a valid idx
int insert_at_k(node **L, int n, int k){
    node* p = malloc(sizeof(node));

    if (!p || k < 0)
        return 0;

    p->d = n;

    if (*L == NULL){
        p->next = NULL;
        *L = p;
        return 1;
    }

    if (k == 0){
        p->next = *L;
        *L = p;
        return 1;
    }

    node* q = *L;
    for (int i = 0; i < k - 1 && q; i++){
        q = q->next;
    }

    if (!q)
        return 0;

    p->next = q->next;
    q->next = p;
    return 1;
}

void printl(node **L){
    node* p = *L;
    while (p){
        printf("%d ", p->d);
        p = p->next;
    }
    printf("\n");
}

void printc(nodec **L){
    nodec* p = *L;
    while (p){
        printf("%c ", p->c);
        p = p->next;
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
        *L = p;
        return 1;
    }

    if (p->d < (*L)->d){ // if p is less than the first element of the list, p will be the new first element
        p->next = *L;
        *L = p;
        return 1;
    } else {
        q = *L;
        while(q->next && p->d > q->next->d){
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
        return 1;
    }
}

int rmv_fr_beg(node **L){
    if (*L == NULL)
        return 1;

    node *p = *L;
    *L = (*L)->next;
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

// Função para remover todos os elementos iguais a x da lista
void remove_x(node** L, int x) {
    node* current = *L;
    node* previous = NULL;

    while (current) {
        if (current->d == x) {
            // Se o valor for igual a x, remova o nó
            if (previous == NULL) {
                // Se o nó a ser removido for o primeiro, atualize a cabeça
                *L = (*L)->next;
                free(current);
                current = *L;
            } else {
                // Caso contrário, ajuste o ponteiro 'next' do nó anterior
                previous->next = current->next;
                free(current);
                current = previous;
            }
        }
        if (current && current->d != x){ // Se current->d for diferente de x, podemos avançar na lista
            previous = current;
            current = current->next;
        }
    }
}

void movenexttofront(struct node* t, node** L){
    if (t == NULL || t->next == NULL)
        return;

    node* p = t->next;
    t->next = t->next->next;
    p->next = *L;
    *L = p;
}

void remove_min(node **L) { // removes the min
    node* p = *L;
    if(p){
        // Primeiro, achamos o mínimo
        int min = (*L)->d;
        while(p){
            if (p->d < min){
                min = p->d;
            }
            p = p->next;
        }

        node *curr = *L;
        node *prev = NULL;
        while (curr){
            if(curr->d == min){
                if(!prev){
                    *L = curr->next;
                    free(curr);
                    curr = *L;
                } else{
                    prev->next = curr->next;
                    free(curr);
                    curr = prev;
                }
            }
            if(curr && curr->d != min){
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

node* copy(node **L1){
    node** L2 = malloc(sizeof(node*));
    *L2 = NULL;
    node* aux = *L1;
    node* q = *L2;

    while(aux){
        node* p = malloc(sizeof(double));
        p->d = aux->d;
        p->next = NULL;
        if (*L2 == NULL){
            *L2 = p;
            aux = aux->next;
            q = *L2;
        } else {
            while (q->next){
                q = q->next;
            }
            q->next = p;
            aux = aux->next;
        }
    }
    return *L2;
}

int comp(node** L1, node** L2){
    node* p1 = *L1;
    node* p2 = *L2;
    while(p1){
        while(p2){

            if(p2->d == p1->d){ // checamos se o p2 atual tem o mesmo conteudo de p1
                break; // se for o caso, passamos para o prox nó de L1
            } else{
                p2 = p2->next;
            }

            if(p1 && !p2){ // se l1 não terminou e l2 terminou, não são iguais
                return 0;
            }
        }
        p1 = p1->next;
        if(p2 && !p1){ // se l1 terminou e l2 não terminou, não são iguais
            return 0;
        }
    }
    return 1;
}

int* list_to_arr(node** L){
    node* p = *L;
    int sz = 0;
    if(p){
        while(p){
            sz++;
            p = p->next;
        }
        int* arr = malloc(sz * sizeof(int));
        p = *L;
        int i = 0;
        while(p){
            arr[i] = p->d;
            i++;
            p = p->next;
        }
        return arr;
    }
    return NULL;
}

void remove_at_idx(nodec** L1, node** L2){ // remove-se de l1, os nós cujos índices serão obtidos em l2
    node* p2 = *L2;
    int j = 1;
    int idx = p2->d - j;
    while(p2){
        nodec* p1 = *L1;
        nodec* prev = NULL;
        for (int i = 0; i < idx; i++){
            if(p1){
                prev = p1;
                p1 = p1->next;
            }else
                break;
        }
        if(p1){
            if(!prev){
                *L1 = (*L1)->next;
            } else{
                prev->next = p1->next;
            }
            free(p1);
            p2 = p2->next;
            j++;
            idx = p2->d - j;
        } else
            break;
    }
}

int fixList(node** L){ // a corrigir
    node* p1 = *L;
    int i = 0;
    while(p1){
        if(p1->next && p1->next->visited){
            p1->next = NULL;
            return 1;
        }
        p1->visited = 1;
        p1 = p1->next;
    }
    if(!p1)
        return 0;
}

nodec* divList(nodec** L){

    nodec* p = *L;
    int Sz = 0;
    // Computamos o tamanho da lista
    while(p){
        p = p->next;
        Sz++;
    }
    int newSz = Sz/2;
    // Criamos a lista dos n/2 primeiros termos
    nodec* q = *L;
    nodec* newList1 = create_listc();
    for(int i = 0; i < newSz; i++){
        pushl(&newList1, q->c);
        q = q->next;
    }
    // Liberamos todos os nós na copiados para newList1
    nodec* prev = NULL;
    q = *L;
    for(int i = 0; i < newSz; i++){
        nodec* aux = q;
        q = q->next;
        *L = q;
        free(aux);
    }
    // Deletamos os nós cujos caracteres não são alfabéticos e minúsculos
    while (q) {
        if (q->c < 'a' || q->c > 'z'){
            // Se o valor for igual a x, remova o nó
            if (prev == NULL) {
                // Se o nó a ser removido for o primeiro, atualize a cabeça
                *L = (*L)->next;
                free(q);
                q = *L;
            } else {
                // Caso contrário, ajuste o ponteiro 'next' do nó anterior
                prev->next = q->next;
                free(q);
                q = prev;
            }
        }
        if (q && q->c >= 'a' && q->c <= 'z'){ // Se current->d for diferente de x, podemos avançar na lista
            prev = q;
            q = q->next;
        }
    }

    return newList1;
}

node* uniteConj(node** A, node** B){ // supondo conjuntos armazenados em listas encadeadas, unimos os conjuntos
    node* newList = create_list();
    node* curra = *A;
    node* currb = *B;
    node* currn = newList;
    while(curra){
        node* p = malloc(sizeof(node));
        p->d = curra->d;
        p->next = NULL;
        if(!p)
            return NULL;
        if(!currn){
            newList = p;
            currn = p;
        } else{
            while(currn->next){
                currn = currn->next;
            }
            currn->next = p;
        }
        curra = curra->next;
    }
    while(currb){
        node* p = malloc(sizeof(node));
        int should_push = 1;
        p->d = currb->d;
        p->next = NULL;
        if(!p)
            return NULL;
        if(!currn){
            newList = p;
        } else{
            while(currn->next){
                currn = currn->next;
            }
            node* test = newList;
            while(test){
                if(test->d == currb->d)
                    should_push = 0;
                test = test->next;
            }
            if(should_push)
                currn->next = p;
        }
        currb = currb->next;
    }
    return newList;
}

node* interConj(node** A, node** B){ // supondo conjuntos armazenados em listas encadeadas, fazemos a sua interseção
    node* newList = create_list();
    node* curra = *A;
    node* currn = newList;
    while(curra){
        node* currb = *B;
        while(currb){
            int should_push = 1;
            if(currb->d == curra->d){
                node* p = malloc(sizeof(node));
                p->d = curra->d;
                p->next = NULL;
                node* test = newList;
                if(!p)
                    return NULL;
                if(!currn){
                    newList = p;
                    currn = p;
                } else{
                    while(currn->next){
                        currn = currn->next;
                    }
                    while(test){
                        if(test->d == currb->d)
                            should_push = 0;
                        test = test->next;
                    }
                    if(should_push)
                        currn->next = p;
                    else
                        free(p);
                }
                break;
            }
            currb = currb->next;
        }
        curra = curra->next;
    }
    return newList;
}

node* minusConj(node** A, node** B){ // supondo conjuntos armazenados em listas encadeadas, fazemos a sua subtracao
    node* newList = create_list();
    node* curra = *A;
    node* currn = newList;
    while(curra){
        int should_push = 1;
        node* currb = *B;
        while(should_push){
            int isatNew = 1;
            if(currb && currb->d == curra->d){
                should_push = 0;
            } else if(!currb && should_push){
                node* p = malloc(sizeof(node));
                p->d = curra->d;
                p->next = NULL;
                node* test = newList;
                if(!p)
                    return NULL;
                if(!currn){
                    newList = p;
                    currn = p;
                } else{
                    while(currn->next){
                        currn = currn->next;
                    }
                    while(test){
                        if(test->d == curra->d)
                            isatNew = 0;
                        test = test->next;
                    }
                    if(isatNew)
                        currn->next = p;
                    else
                        free(p);
                }
                should_push = 0;
            }
            if(currb)
                currb = currb->next;
        }
        curra = curra->next;
    }
    return newList;
}

//lista encadeada exogena
typedef struct data{

    int k; //chave
    char* str; //nome
    double v; //valor
    
}data;

typedef struct nodex{

    data* d;
    struct nodex* next;

}nodex;


int injectex(nodex **L, data* dat){
    nodex* p = malloc(sizeof(nodex));

    if (!p)
        return 0;

    p->d = dat;
    p->next = *L;
    *L = p;
    return 1;
}

int main(){
    nodec* L1 = create_listc();
    node* L2 = create_list();
    node* L3 = create_list();

    push(&L2, 17);
    push(&L2, 19);
    push(&L2, 17);
    push(&L2, 17);
    push(&L2, 5);
    push(&L2, 23);
    push(&L2, 1);

    push(&L3, 17);
    push(&L3, 19);
    push(&L3, 17);
    push(&L3, 17);
    push(&L3, 5);
    push(&L3, 8);
    push(&L3, 1);

    //node* set = minusConj(&L2, &L3);
    //printl(&set);
    /*printc(&L1);
    printf("\n");
    nodec* L3 = divList(&L1);
    printc(&L3);
    printf("\n");
    printc(&L1);
    printf("\n");*/
    node* p = L2;
    while(p->d != 1){
        p = p->next;
    }
    node* q = L2;
    while(q->d != 17 && q != L2){
        q = q->next;
    }
    p->next = q;
    fixList(&L2);
    printl(&L2);
}