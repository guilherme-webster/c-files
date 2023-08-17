#include <stdio.h>
#include <string.h>

#define MAX_PALAVRA 20

/*
modifique esse arquivo criando uma função
que copia uma palavra da maneira com que
o cebolinha falaria
*/

int comprimento_str(char string[]) {
    int comprimento = 0;
    while (string[comprimento] != '\0') {
        comprimento += 1;
    }
    return comprimento;
}

void copiar_cebolinha(char palavra[], char modificada[]) {
    int i, j;
    int ult_eh_erre = 0;
    j = 0;
    int comprimento;
    comprimento = comprimento_str(palavra);                          /* índice da primeira posição de inverso */
    for (i = 0; i <= comprimento - 1; i++) {
        if (palavra[i] == 'R'){
            if (ult_eh_erre == 0) {
                modificada[j] = 'L';
                j += 1;
            }
            ult_eh_erre = 1;
        } else{
            modificada[j] = palavra[i];
            j += 1;
            ult_eh_erre = 0;
        }
    }
    /* adicionamos o '\0' para indicar que a string terminou */
    modificada[j] = '\0';
}

int main() {
    char palavra[MAX_PALAVRA];
    char modificada[MAX_PALAVRA];

    scanf("%s", palavra);
    copiar_cebolinha(palavra, modificada);
    printf("%s", modificada);
}
