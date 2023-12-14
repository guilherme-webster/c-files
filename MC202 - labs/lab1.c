#include <stdio.h>

// Checa se dois números sao amigos. Exemplo: Os divisores próprios de 284 são 1, 2, 4, 71 e 142, que somam 220, e os divisores próprios de 220 somam 284. Dois números distintos que respeitam esta propriedade são amigos.

int soma_divisores(int n){
    int i;
    int sum;
    sum = 0;
    for (i = 1; i <= n / 2; i++){
        if (n % i == 0){ //iteramos sobre i, de modo a achar os restos quando este divide n
            sum += i; //se for divisor, somamos
        }
    }
    return sum;
}

int main(){
    int n, m;
    int sum1, sum2;
    sum1 = 0;
    sum2 = 0;
    scanf("%d %d", &n, &m);
    sum1 = soma_divisores(n);
    sum2 = soma_divisores(m);
    if (sum1 == m && sum2 == n){ //comparamos a soma dos divisores com o possível amigo
        printf("%d e %d sao amigos\n", n, m);
    } else {
        printf("%d e %d nao sao amigos\n", n, m);
    }
    return 0;
}
