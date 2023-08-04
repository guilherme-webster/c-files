#include <stdio.h>

#define MAX_ALUNOS 100


float ler_media(int m) {
    int i;
    float media, nota;
    media = 0;
    for (i = 0; i < m; i++) {
        scanf("%f", &nota);
        media += nota;
    }
    media = media / m;
    return media;
}


void ler_notas_praticas(float P[MAX_ALUNOS], int n){
    int i;
    for (i = 0; i < n; i ++){
        P[i] = ler_media(3);
    }
}


void ler_notas_teoricas(float T[MAX_ALUNOS], int n){
    int i;
    for (i = 0; i < n; i ++){
        T[i] = ler_media(2);
    }
}


float obter_maximo(float vetor[MAX_ALUNOS], int n){
    int i; 
    float maximo = vetor[0];
    for (i = 0; i < n; i++){
        if (vetor[i] > maximo){
            maximo = vetor[i];
        }
    }
    return maximo;
}


void multiplica_fator(float vetor[MAX_ALUNOS], int n, float fator){
    int i;
    for (i = 0; i < n; i++){
        vetor[i] = vetor[i] * fator;
    }
}


void altera_t(float vetor[MAX_ALUNOS], int n){
    int i;
    float maior_t;
    maior_t = obter_maximo(vetor, n);
    for (i = 0; i < n; i++){
        vetor[i] = 10 * vetor[i] / maior_t;
    }
}


void medias(float P[MAX_ALUNOS], float T[MAX_ALUNOS], float F[MAX_ALUNOS],int n){
    int i;
    for (i = 0; i < n; i++){
        F[i] = (P[i] + T[i]) / 2;
    }
}


float calcular_medias(float vetor[MAX_ALUNOS], int m){
    int media_v;
    int j;
    media_v = 0;
    for (j = 0; j < m; j++){
        media_v += vetor[j];
    }
    media_v /= m;
    return media_v;
}


int main() {
    int n;
    int i, j, l;
    float P[MAX_ALUNOS];
    float T[MAX_ALUNOS];
    float F[MAX_ALUNOS];
    float maximo;
    float maximo_t;
    float media_p;
    float media_t;
    media_p = 0;
    scanf("%d", &n);
    ler_notas_praticas(P, n);
    ler_notas_teoricas(T, n);
    multiplica_fator(P, n, 1.1);
    altera_t(T, n);
    medias(P, T, F, n);
    for (j = 0; j < n; j++){
        media_p = media_p + P[j];
    }
    media_p /= n;
    for (l = 0; l < n; l++){
        media_t = media_t + T[l];
    }
    media_t /= n;
    for (i = 0; i < n; i++){
        printf("%f\n", F[i]);
    }
    maximo = obter_maximo(P, n);
    maximo_t = obter_maximo(T, n);
    printf("Max P: %f\n", maximo);
    printf("Max T: %f\n", maximo_t);
    printf("%f\n", media_p);
    printf("%f\n", media_t);
    return 0;
}