#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 Uma aplicação precisa manter um glossário que registra a ordem em que um conjunto de cadeias foram adicionadas a ele.

Implemente uma tabela de hashing para armazenar o glossário dessa aplicação. A tabela deve armazenar pares formados por uma cadeia e um timestamp. Um timestamp é um número natural único e seqüencial, a partir de 0 e sem reuso que indica o momento que a cadeia foi inserida na tabela.

As colisões devem ser resolvidas usando sondagem com incremento por hashing dupla.
*/

// 0xFFFFFFFFFFFFFFFF representa uma posicao vazia e 0xFFFFFFFEFFFFFFFE uma posicao nunca acessada

typedef struct data{
    char *str;
    unsigned long key;
    int tstp;
}data;


void initializeTable(data t[], int SZ){
    int i;

    for(i = 0; i < SZ; i++){
        t[i].key = 0xFFFFFFFFFFFFFFFF; // supor que este numero não será resultado do djb2
        t[i].str = NULL;
    }
}

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int next_prime(int n) {
    while (!is_prime(n)){
        ++n;
    }
    return n;
}

unsigned long djb2(char *str) {
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) ^ c; // hash * 33 XOR c
  
  return hash;
}

char* strnew(char* str) {
    size_t length = strlen(str);
    char* new_str = malloc(length + 1);
    if (new_str != NULL) {
        memcpy(new_str, str, length);
        new_str[length] = '\0';
    }
    return new_str;
}

int hash(unsigned long k, int i,int SZ){
    return (k % SZ + i * ((k % (SZ - 2)) + 1)) % SZ;
}

int search(data t[], char *str, int SZ){
    unsigned long value = djb2(str);
    int i = 0;
    int id = hash(value, i, SZ);
    while(t[id].key != 0xFFFFFFFFFFFFFFFF){ // 0xFFFFFFFFFFFFFFFF representa uma posicao vazia e 0xFFFFFFFEFFFFFFFE uma posicao nunca acessada
        if(t[id].key != 0xFFFFFFFEFFFFFFFE && strcmp(t[id].str, str) == 0){
            return t[id].tstp;
        }else{
            i++;
            id = hash(value, i, SZ);
        }
    }
    return -1;
}

int insert(data t[], char *str, int SZ, int timestamp){
    unsigned long value = djb2(str);
    int i = 0;
    int id = hash(value, i, SZ);

    int find = search(t, str, SZ);
    if(find != -1)
        return 0;

    while(t[id].key != 0xFFFFFFFFFFFFFFFF && t[id].key != 0xFFFFFFFEFFFFFFFE){
        i++;
        id = hash(value, i, SZ);
    }
    
    t[id].str = strnew(str);
    t[id].tstp = timestamp;
    t[id].key = value;
    return 1;
}

int copy(data t[], data info, int SZ){
    unsigned long value = djb2(info.str);
    int i = 0;
    int id = hash(value, i, SZ);
    while(t[id].key != 0xFFFFFFFFFFFFFFFF && t[id].key != 0xFFFFFFFEFFFFFFFE){
        if(t[id].key == value)
            break;

        i++;
        id = hash(value, i, SZ);
    }
    if(t[id].key != value){
        t[id].str = strnew(info.str);
        t[id].tstp = info.tstp;
        t[id].key = value;
        return 1;
    }
    return 0;
}

data* rd(data t[], int* SZ){
    int nSZ = next_prime(2 * *(SZ));
    data* newTable = malloc(sizeof(data) * nSZ);
    initializeTable(newTable, nSZ);
    for(int j = 0; j < *SZ; j++){
        if(t[j].key != 0xFFFFFFFFFFFFFFFF && t[j].key != 0xFFFFFFFEFFFFFFFE)
            copy(newTable, t[j], nSZ);
    }

    for(int j = 0; j < *SZ; j++){
        if(t[j].str)
            free(t[j].str);
    }
    free(t);
    *SZ = nSZ;
    return(newTable);
}

void delete(data t[], char *str, int SZ){
    unsigned long value = djb2(str);
    int i = 0;
    int id = hash(value, i, SZ);
    while(t[id].key != 0xFFFFFFFFFFFFFFFF){
        if(t[id].key != 0xFFFFFFFEFFFFFFFE && strcmp(t[id].str, str) == 0){
            t[id].key = 0xFFFFFFFEFFFFFFFE;
            t[id].str = NULL;
            return;
        }else{
            i++;
            id = hash(value, i, SZ);
        }
    }
}

int main(){
    char cmd;
    int sz = 3;
    int hashsz = 0;
    int check;
    int timestamp = 0;
    float cf = 0;
    data* table = malloc(sizeof(data) * sz);
    initializeTable(table, sz);

    while (1){

        scanf("%c", &cmd);
        getchar();

        if (cmd == 'c'){
            int n;
            scanf("%d", &n);

            if(table){
                for(int j = 0; j < sz; j++){
                    if(table[j].str)
                        free(table[j].str);
                }
                free(table);
            }

            sz = next_prime(n);
            cf = (float)hashsz / sz;
            if(cf > 0.7)
                sz = next_prime(2 * sz);
            table = malloc(sizeof(data) * sz);
            initializeTable(table, sz);
            timestamp = 0;
            hashsz = 0;
            getchar();
        }

        if (cmd == 'i'){
            char str[251] = { '\0' };
            scanf("%[^\n]", str);
            check = insert(table, str, sz, timestamp);
            if(check)
            {
                hashsz++;
                timestamp = timestamp + 1;
            }
            cf = (float)hashsz / sz;
            if(cf > 0.7){
                table = rd(table, &sz);
            }
            getchar();
        }

        if (cmd == 'r'){
            char str[251] = { '\0' };
            scanf("%[^\n]", str);
            delete(table, str, sz);
            getchar();
        }

        if (cmd == 'b'){
            char str[251] = { '\0' };
            scanf("%[^\n]", str);
            int find = search(table, str, sz);
            if(find > -1){
                printf("[%s] esta na tabela, timestamp %d\n", str, find);
            }else if(find == -1){
                printf("[%s] nao esta na tabela\n", str);
            }
            getchar();
        }

        if (cmd == 'f'){
            if(table){
                for(int j = 0; j < sz; j++){
                    if(table[j].str)
                        free(table[j].str);
                }
                free(table);
            }
            return 0;
        }
    }
}
