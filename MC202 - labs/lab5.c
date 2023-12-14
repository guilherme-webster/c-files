#include <stdio.h>
#include <string.h>

/*
Um palíndromo é uma cadeia de caracteres que é igual à sua reversa, por exemplo abcdcba. O comprimento de um palíndromo é o número de caracteres que ele tem. Letras minúsculas e maiúsculas são consideradas iguais para esta definição de palíndromo.
Um 2-palíndromo é uma cadeia de caracteres que tem pelo menos 2 palíndromos diferentes como subcadeia, cada um com comprimento maior ou igual a 3 e que não sejam um contido no outro. Palíndromos em um 2-palíndromo podem se sobrepor parcialmente. Por exemplo, a cadeia Abana é um 2-palindromo e a cadeia BAAAAAB não é.

Escreva um progrma para copiar somente 2-palíndromos da entrada para a saída.

Entrada
A entrada tem uma ou mais linhas. Cada linha contém zero ou mais palavras separadas por um ou mais espaços. As palavras contêm somente letras sem acentos. Cada linha contém no máximo 256 caracteres.
Saída
A saída deve conter um 2-palíndromo por a linha, na ordem de ocorrência e com a mesma grafia da entrada.
*/

#define SIZE 50

#define MAX_SIZE 100

int count_word(char str[SIZE]){
    int c = 0;
    while (str[c] != '\0')
        ++c;
    return c;
}

void capitalize(char str[SIZE], char temp[SIZE],int sz){
    int i;

    for (i = 0; i <= sz - 1; i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
                temp[i] = str[i] + 'A' - 'a';
        } else{
            temp[i] = str[i];
}}}

void invert(char str[SIZE], int sz, char inverse[SIZE]){
    int i;

    for (i = 0; i < sz; i++)
        inverse[i] = str[sz - i - 1];
}

int str_compare(char str1[SIZE], char str2[SIZE], int i){
    int j;
    for (j = 0; j < i; j++){
        if (str1[j] != str2[j])
            return 0;
    }
    return 1;
}

int is_present(char arr[MAX_SIZE][SIZE], char sbstr[], int sbsz,int idx){
    int isElementPresent = 0;
     
    for (int i = 0; i < MAX_SIZE; i++) {
        if (str_compare(arr[i], sbstr, sbsz)) {
            isElementPresent = 1;
            break;
        }
    }
     
    if (isElementPresent)
        return 1; 
    else
        for (int o = 0; o < sbsz; o++){
            arr[idx][o] = *(sbstr + o); 
        }
        return 0;   
    }

int is_2palindrome(char str[SIZE], int sz){
    int i = 0, j = 0, k = 0, p = 0,counter = 0, idx = 0, should_count = 1, isElementpresent = 0;
    char subpalindromes[MAX_SIZE][SIZE];

    for (i = 3; i <= sz / 2; i++){
        char sub[i], inverse[i];
        memset(sub, 0, i);
        memset(inverse, 0, i);
        for (k = 0; k <= sz / 2; k++){
            for (j = 0; j < i; j++){
                sub[j] = str[k + j];
            }

            invert(sub, i, inverse);

            if (str_compare(sub, inverse, i)){
                isElementpresent = is_present(subpalindromes, inverse, i, idx);
                if (isElementpresent == 0){
                    ++idx;
                    for (p = 0; p < idx; p++){
                        if(strstr(inverse, subpalindromes[p]) != NULL && isElementpresent)
                            should_count = 0; // talvez tenhamos q por \0 no fim dos arrays
                        else
                            should_count = 1;
                    }
                    if (should_count)
                        ++counter;
                }
            }
            }}

    if (counter >= 2)
        return 1;
    else
        return 0;
    }

int main(){
    int sz;
    char str[SIZE], temp[SIZE];

    while(scanf("%s", &str) == 1){
        sz = count_word(str);
        capitalize(str, temp, sz);
        if (is_2palindrome(temp, sz))
            printf("%s\n", str);
        memset(str, 0, SIZE);
        memset(temp, 0, SIZE);
    }
    return 0;
    }
