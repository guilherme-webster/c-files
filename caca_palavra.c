#include <stdio.h>
#include <string.h>


#define MAX_PALAVRA 15

#define MAX_ALTURA 15

#define MAX_LARGURA 10

void le_matriz(char matriz[MAX_ALTURA][MAX_LARGURA],int m,int n) {
    int i,j;
    char letra;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            scanf(" %c", &letra);
            matriz[i][j] = letra;
        }
    }
}

void cria_matriz_ponto(char matriz[MAX_ALTURA][MAX_LARGURA], int m, int n){
    int i,j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            matriz[i][j] = '.';
        }
    }
}

void imprime_matriz(char matriz[MAX_ALTURA][MAX_LARGURA], int m, int n){
    int i,j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("%c ",matriz[i][j]);
        }
        printf("\n");
    }
}

void search_word(char A[MAX_ALTURA][MAX_LARGURA], char B[MAX_ALTURA][MAX_LARGURA], char word[], int m, int n){
    int directions[8][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}};
    int word_length = strlen(word);
    int i,j,d,k;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            for (d = 0; d < 8; d++){
                int dr = directions[d][0];
                int dc = directions[d][1];
                int end_row = (word_length - 1) * dr + i;
                int end_col = (word_length - 1) * dc + j;

                if (end_row >= 0 && end_row < m && end_col >= 0 && end_col < n){
                    int temp_row = i;
                    int temp_col = j;
                    int found = 1;

                    for (k = 0; k < word_length; k++){
                        if (A[temp_row][temp_col] != word[k]){
                            found = 0;
                            break;
                        }
                    temp_row += dr;
                    temp_col += dc;
                    }
                    if (found){
                        temp_row = i;
                        temp_col = j;
                        for (i = 0; i < word_length; i++){
                            B[temp_row][temp_col] = word[i];
                            temp_row += dr;
                            temp_col += dc;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    int i;
    int m,n;
    char palavra[MAX_PALAVRA], inverso[MAX_PALAVRA];
    char A[MAX_ALTURA][MAX_LARGURA];
    char B[MAX_ALTURA][MAX_LARGURA];
    int p;

    scanf("%d %d", &m, &n); // le as dim. da matriz
    le_matriz(A, m, n);
    cria_matriz_ponto(B, m, n);

    scanf("%d", &p);
    for (i = 0; i < p; i++){
        scanf("%s", palavra);
        search_word(A, B, palavra, m, n);
    }
    imprime_matriz(B, m, n);
}