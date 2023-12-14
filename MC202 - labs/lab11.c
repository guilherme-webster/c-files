#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Escreva um programa para construir uma lista encadeada para cadeias, inteiros, fracionários e caracteres com operações para inverter e transpor trechos da lista.
*/

typedef struct node{
    char type; // s,d,f,c 
    void* data;
    struct node* next;
}node;

node* createList(){
  node** L = malloc(sizeof(node*));
  *L = NULL;
  return *L;
}

node* createInt(int i){
  int* intpointer = (int*)malloc(sizeof(int));
  node* item = (node*)malloc(sizeof(node));
  *intpointer = i;
  item->type = 'd';
  item->data = intpointer;
  item->next = NULL;
  return item;
}

node* createFloat(float f){
  float* floatpointer = (float*)malloc(sizeof(float));
  node* item = (node*)malloc(sizeof(node));
  *floatpointer = f;
  item->type = 'f';
  item->data = floatpointer;
  item->next = NULL;
  return item;
}

node* createStr(char* s){
  char* strpointer = (char*)malloc(129 * sizeof(char));
  node* item = (node*)malloc(sizeof(node));
  strpointer = strcpy(strpointer, s);
  item->type = 's';
  item->data = strpointer;
  item->next = NULL;
  return item;
}

node* createChar(char c){
  char* charpointer = (char*)malloc(sizeof(char));
  node* item = (node*)malloc(sizeof(node));
  *charpointer = c;
  item->type = 'c';
  item->data = charpointer;
  item->next = NULL;
  return item;
}

int inject(node **L, node *p){

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

void reverse(node **L, int b, int e){ // 'b' é o comeco da reversao e 'e' o final
  node* prev = NULL;
  node* curr = *L;
  node* next;
  int i = 0;
  int counter = 1;

  if (!(*L))
    return;

  if (b < 0 || e < 0)
    return;

  if (b >= e)
    return;
  
  while(curr && i < b){
    prev = curr;
    curr = curr->next;
    counter++;
    i++;
  }

  if(!curr)
    return;

  // strt é o no imediatamente anterior ao comeco da reversao
  node* strt = prev;
  // comeco da reversao
  node* newstrt = curr; 
  while(curr && i <= e){
    next = curr->next;
    curr->next = prev;  // neste while, invertem-se as "setas" da lista
    prev = curr;
    curr = next;
    counter++;
    i++;
  }

    if(!curr && counter < e - b)
      return;

    if(strt) // se nao invertemos o comeco da lista, conectamos a inversao com o imediatamente anterior
      strt->next = prev;
    else
      *L = prev; //  se estivermos invertendo o comeco, devemos atualizar o head

  if(newstrt)
    newstrt->next = curr; // conectamos a parte apos a reversao com a revertida
}

void trans(node ** L, int b, int e, int k)
{
    node *current = *L;
    node *prev = NULL;
    int i = 0;
    int counter = 1;

    if (*L == NULL) {
	    return;			// lista esta vazia
    }

    if (b > e) {
	    return;			// nao é possível transpor se i for maior a j
    }

    if (b < 0 || e < 0)
      return;

    while (current && i < b) {	// acha o primeiro elemento da transposicao
	    prev = current;
	    current = current->next;
      counter++;
	    i++;
    }

    if(!current)
      return;

    node* prevstart = prev; // no antes de i
    node* start = current; // no i

    while (current && i < e) {	// acha o ultimo elemento da transposicao
	    current = current->next;
      counter++;
	    i++;
    }

    if(!current && counter < e - b)
      return;

    node* end = current; // no j

    current = *L;		// irá apontar para o k-ésimo nó (ou para o primeiro, se k == -1)
    prev = NULL;
    i = 0;
    counter = 1;

    if (k != -1) {

	    while (current && i < k) {
	        prev = current;
          current = current->next;
          counter++;
	        i++;
	    }


	   if(!current && counter < k)
        return;

	  node* target = current; // no  k
    
	  if (prevstart)
	    prevstart->next = end->next;
      else
        *L = end->next;

    if(target){
      end->next = target->next;
      target->next = start;
    }

    }else{
      if(prevstart){
        prevstart->next = end->next;
        end->next = *L;
        *L = start;
      }
    }
}

void printl(node **L){
  node* p = *L;
  while (p){
      if(p && p->type == 'd'){
        printf("%d ", *((int *)p->data));
      }
      if(p && p->type == 'f'){
        printf("%.4f ", *((float *)p->data));
      }
      if(p && p->type == 'c'){
        printf("%c ", *((char *)p->data));
      }
      if(p && p->type == 's'){
        printf("%s ", ((char *)p->data));
      }
      p = p->next;
  }
  printf("\n");
}

void freel(node **L) {
  while (*L) {
    node *aux = *L;
    *L = (*L)->next;
    if (aux){
      if(aux->data)
        free(aux->data); // Libera a memória alocada para o dado
      free(aux); // Libera o no que apontava para o dado
    }
  }
}

int main(){
  char cmd;
  node* L1 = NULL;
  while (1){

    scanf("%c", &cmd);
    
    if (cmd == 'c') {
      getchar();
      if (L1){
        freel(&L1);
      }
      L1 = createList();
    }

    if (cmd == 'i'){
      char t;
      scanf(" %c ", &t);
      if(t == 's'){
        char s[128];
        scanf("%[^\n]", s);
        getchar();
        node* strNode = createStr(s);
        inject(&L1, strNode);
      }
      if(t == 'd'){
        int i;
        scanf("%d", &i);
        getchar();
        node* intNode = createInt(i);
        inject(&L1, intNode);
      }
      if(t == 'f'){
        float x;
        scanf("%f", &x);
        getchar();
        node* floatNode = createFloat(x);
        inject(&L1, floatNode);
      }
      if(t == 'c'){
        char c;
        scanf("%c", &c);
        getchar();
        node* charNode = createChar(c);
        inject(&L1, charNode);
      }
    }

    if (cmd == 'r'){
      int i,j;
      scanf(" %d %d", &i, &j);
      getchar();
      reverse(&L1, i, j);
    }

    if (cmd == 't'){
      int i,j, k;
      scanf(" %d %d %d", &i, &j, &k);
      getchar();
      trans(&L1, i, j, k);
    }

    if (cmd == 'p'){
      getchar();
      printl(&L1);
    }

    if (cmd == 'f'){
      freel(&L1);
      return 0;
    }
  }
}
