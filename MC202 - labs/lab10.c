#include <stdio.h>
#include <stdlib.h>

/*
 Uma matriz é esparsa se tem proporcionalmente muitos zeros. "Muitos" não é uma quantidade definida claramente, mas em geral se uma matriz com m linhas e n colunas tem um número de entradas não-zero da ordem de m+n então ela é considerada esparsa.
Quando uma matriz esparsa é colocada na memória, uma parte significativa do espaço é usada para armazenar zeros, que em muitos casos é simplesmente ausência de informação.

Estruturas de dados para matrizes esparsas não armazenam os zeros. Elas sacrificam o tempo de acesso constante a qualquer elemento oferecido pelas matrizes para usar menos memória. Algumas estruturas de dados para matrizes esparsas são melhores para percorrer os elementos de uma mesma linha ou coluna da matriz. Algumas são boas para recuperação mas piores para atualização da matriz, e vice-versa.

Uma dessas representações é como uma lista endadeada de listas encadeadas, ou simplesmente lista de listas. Cada lista armazena os elementos de uma linha i em que cada elemento armazena uma dupla (j,elemento).
 */

typedef struct noden{

    int lin;
    int col;
    int d; 
    struct noden* next;

}noden;

typedef struct nodel{

    int lin;
    struct noden* line;
    struct nodel* next;

}nodel;

nodel* create_listl(){
    nodel** L = malloc(sizeof(nodel*));
    *L = NULL;
    return *L;
}

noden* create_listn(){
    noden** L = malloc(sizeof(noden*));
    *L = NULL;
    return *L;
}

void printm(nodel **L){
    nodel* p = *L;
    if (!p)
        printf("A matriz e' nula.");
    else{
        printf("M: ");
        while(p){
            noden* q = p->line;
            while(q){
                printf("(%d,%d,%d) ", q->lin, q->col, q->d);
                q = q->next;
            }
            p = p->next;
        }
    }
    printf("\n");
}

noden* remove_c(noden **L, int l, int c){

    noden* q = *L;
    noden* prev = *L;
    if(!(*L)) // removemos o elemento de uma linha vazia
        return *L;
    if (!(*L)->next && q->lin == l && q->col == c){ // removemos o elemento de uma linha com um único elemento
        free(*L);
        *L = NULL;
        return *L;
    } 
    while(q->next && q->next->col <= c){
        prev = q;
        prev->next = q->next;
        q = q->next;
    }
    if(q->lin == l && q->col == c){
        if (q->next) {
            if (q == *L){ // remove o primeiro
                *L = (*L)->next;
                free(q);
                q = *L;
                return *L;
            } else { // caso que retiramos um nó do meio
                prev->next = q->next;
                free(q);
                return *L;
            }
        } else { // retiramos do final da linha
            prev->next = NULL;
            free(q);
            return *L;
        }
    }
    return *L;
}

nodel* remove_l(nodel **L, int l){

    nodel* q = *L;
    nodel* prev = *L;
    if(!(*L)) // removemos o elemento de uma linha vazia
        return *L;
    if (!(*L)->next && q->lin == l){ // removemos o elemento de uma linha com um único elemento
        free(*L);
        *L= NULL;
        return *L;
    } 
    while(q->next && q->next->lin <= l){
        prev = q;
        prev->next = q->next;
        q = q->next;
    }
    if(q->lin == l){
        if (q->next) { // remove o primeiro
            if (q == *L){
                *L = (*L)->next;
                free(q);
                q = *L;
                return *L;
            } else { // caso que retiramos um nó do meio
                prev->next = q->next;
                free(q);
                return *L;
            }
        } else { // retiramos do final da linha
            prev->next = NULL;
            free(q);
            return *L;
        }
    }
    return *L;
}

noden* set_in_l(noden **L, int l, int c, int n){

    if(n){
        noden* p = malloc(sizeof(noden));
        p->lin = l;
        p->col = c;
        p->d = n;
        if (*L == NULL){ // add na linha nula
            p->next = NULL;
            (*L) = p;
            return *L;
        }

        noden* q = *L;

        while(q->next && q->next->col <= c)
            q = q->next;
        if (!q->next && c > q->col){ // add no fim
            p->next = NULL;
            q->next = p;
            return *L;
        }
        if (q->next && q->next->col > c && c > q->col){ // add no meio
            p->next = q->next;
            q->next = p;
            return *L;
        }
        if (c < q->col){ // add no começo
            p->next = *L;
            *L = p;
            return  *L;
        }
        if (c == q->col){ // apenas altera um valor ja existente em alguma coluna que ja guarda um elemento não nulo
            q->d = n;
            free(p);
            return  *L;
        }
    } else{
        return *L = remove_c(L, l, c); // adicionamos um zero, ou seja, removemos um elemento ou nao fazemos nada
    }
    return *L; // não entrou em nenhum dos casos anteriores
}

int set(nodel **L1, int l, int c, int n){

    if (*L1 == NULL){ // adicionamos uma linha numa lista nula
        nodel* q = malloc(sizeof(nodel));
        q->lin = l;
        q->line = NULL;
        q->line = set_in_l(&(q->line), l, c, n);
        if(q->line){ 
            q->next = NULL;
            (*L1) = q;
        } 
        if(!q->line && !n){ // adicionamos um zero, ou seja, removemos um elemento ou nao fazemos nada
            *L1 = remove_l(L1, l);
            free(q);
        }
        return 1;
    }
    nodel* p = *L1;
    while(p->next && p->next->lin <= l){
        p = p->next;
    }
    if (p->lin == l){ // não criamos uma nova linha, mas adicionamos ou retiramos uma coluna
        p->line = set_in_l(&(p->line), l, c, n);
        if(!p->line && !n) // adicionamos um zero, ou seja, removemos um elemento ou nao fazemos nada
            *L1 = remove_l(L1, l);
        return 1;
    }
    if(!p->next && l > p->lin){ // adicionamos uma linha no final
        nodel* q = malloc(sizeof(nodel));
        q->lin = l;
        q->line = NULL;
        q->line = set_in_l(&(q->line), l, c, n);
        if(q->line){
            p->next = q;
            q->next = NULL;
        }
        if(!q->line && !n){ // adicionamos um zero, ou seja, removemos um elemento ou nao fazemos nada
            *L1 = remove_l(L1, l);
            free(q);
        }
        return 1;
    }
    if (p->next && p->next->lin > l && l > p->lin){ // adicionamos uma linha no meio da lista
        nodel* q = malloc(sizeof(nodel));
        q->lin = l;
        q->line = NULL;
        q->line = set_in_l(&(q->line), l, c, n);
        if(q->line){
            q->next = p->next;
            p->next = q;
        } 
        if(!q->line && !n){ // adicionamos um zero, ou seja, removemos um elemento ou nao fazemos nada
            *L1 = remove_l(L1, l);
            free(q);
        }
        return 1;
    }
    if (l < p->lin){ // adicionamos uma linha no começo da lista
        nodel* q = malloc(sizeof(nodel));
        q->lin = l;
        q->line = NULL;
        q->line = set_in_l(&(q->line), l, c, n);
        if(q->line){
            q->next = *L1;
            (*L1) = q;
        } 
        if(!q->line && !n){ // adicionamos zero, ou seja removemos alguma coluna, ou linha inteira, ou mantemos a matriz como está
            *L1 = remove_l(L1, l);
            free(q);
        }
        return 1;
    }
    return 0; // não entrou em nenhum dos casos anteriores
}

void get(nodel** L, int l, int c){
    nodel* p = *L;
    if(p){
        while(p->next && p->next->lin <= l){
            p = p->next;
        }
        noden* q = p->line;
        while(q->next && q->next->col <= c){
            q = q->next;
        }
        if (p->lin == l && q->col == c)
            printf("M[%d][%d] == %d\n", p->lin, q->col, q->d);
        else
            printf("M[%d][%d] == %d\n", l, c, 0);
    } else
        printf("M[%d][%d] == %d\n", l, c, 0);
}

int main(){
    char cmd;
    nodel* L1 = NULL;

    while (1){
        scanf("%c", &cmd);
        getchar();
        

        if (cmd == 'c') {
            if (L1){
                free(L1);
            }
            L1 = create_listl(); // lista de listas
        }

        if (cmd == 'a'){
            int l, c, n;
            scanf("[%d,%d] %d", &l, &c, &n);
            getchar();
            set(&L1, l, c, n);
        }
        
        if (cmd == 'r'){
            int l, c;
            scanf("[%d,%d]", &l, &c);
            getchar();
            get(&L1, l, c);
        }

        if (cmd == 'p')
            printm(&L1);


        if (cmd == 't')
            return 0;
    }
}
