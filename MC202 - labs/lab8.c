#include <stdio.h>
#include <stdlib.h>

/*
 Vladimir trabalhou por muitos anos fazendo Matrioscas, aquelas bonecas aninhadas que representam o ofício russo. Uma matriosca é uma boneca que pode ser aberta, de modo que dentro dela se encontra outra boneca. Então, esta segunda boneca pode ser novamente aberta para se encontrar outra. Este processo pode ser repetido até que uma boneca final, que não pode ser aberta, seja encontrada.
Recentemente, Vladimir percebeu que a idéia de bonecas Matrioscas pode ser generalizada para brinquedos aninhados. Dessa forma, ele projetou brinquedos que contêm brinquedos, introduzindo um novo recurso: um brinquedo desses, ao ser aberto, pode conter um ou mais brinquedos em seu interior. Estes novos brinquedos são chamados de Matrioscas Generalizadas.
Um brinquedo é representado por um número inteiro positivo, que é seu tamanho. Dentro de um brinquedo M encontram-se os brinquedos n1,n2,...,nr, de forma que n1+...+nr < M.Nesse caso, dizemos que o brinquedo contém diretamente os brinquedos n1,n2,...,nr. Entretanto, não contém diretamente os brinquedos que estão dentro dos brinquedos n1,...,nr.
 */

typedef struct {
    int sz_mat;
    int internal_sz_mat;
} Matriosca;

// Função para empilhar um elemento
void push(Matriosca *s, int *stacksz,int value, int max)
{
    Matriosca m;
    m.sz_mat = value;
    m.internal_sz_mat = 0;
    if (*stacksz < max) {
        s[*stacksz] = m;
        (*stacksz)++;
    }
}

// Função para desempilhar um elemento
int pop(int max, Matriosca s[max], int *stacksz) 
{
    Matriosca y;
    if (*stacksz > 0) {
        (*stacksz)--;
        y = s[*stacksz];
        return y.sz_mat;
    } else
        return 0;
}


int main() {
    int n;

    while (1) {

        int isMatriosca = 1;

        scanf("%d", &n);

        if (n == 0)
         break;

        Matriosca stack[n];
        int stacksz = 0;

        for (int i = 0; i < n; i++) {
            int j;
            scanf("%d", &j);
            if (j < 0){ // Empilhamos os negativos
                push(stack, &stacksz,j, n);
                if (stacksz > 1)
                    stack[stacksz - 2].internal_sz_mat += j; // Fazemos a soma das matrioscas imediatamente internas
            } else if (j != -stack[stacksz - 1].sz_mat)
                isMatriosca = 0;
                else {
                    pop(n, stack, &stacksz);
                    if (stacksz != 0){
                        if (stack[stacksz - 1].internal_sz_mat <= stack[stacksz - 1].sz_mat) // Garantimos que a soma das matrioscas internas é menor que a externa
                            isMatriosca = 0;
                    }
                }
        }
        
        if (isMatriosca) {
            printf(":-) Matriosca!\n");
        } else {
            printf(":-( Tente novamente.\n");
        }
    }
    
    return 0;
}
