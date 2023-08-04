#include <stdio.h>

int main(){
    int i,j, n, duracao, limite, maxima;
    int velocidades[100];

    scanf("%d", &n); /* numero de lesmas */ 

    for (i = 0; i < n; i++) {
        scanf("%d", &velocidades[i]);
    }

    scanf("%d", &duracao);

    if (duracao == 1) {
        limite = 100;
    } else if (duracao == 2) {
        limite = 20;
    } else if (duracao == 3) {
        limite = 10;
    }

    maxima = 0;
    for (j = 0; j < n; j++){
        if (velocidades[j] > maxima && velocidades[j] <= limite) {
            maxima = velocidades[j];
        }
    }
    printf("%d\n", maxima);
}
