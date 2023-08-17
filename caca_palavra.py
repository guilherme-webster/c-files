def le_matriz(matriz, m):
    for i in range(m):
        linha = input().split()
        matriz.append(linha)
    return matriz


def cria_matriz_ponto(m, n):
    matriz_ponto = []
    for i in range(m):
        linha = []
        for j in range(n):
            linha.append('.')
        matriz_ponto.append(linha)
    return matriz_ponto
    


def print_matriz(matriz, m, n):
    for i in range(m):
        for j in range(n):
            print(matriz[i][j], end=' ')
        print()


def copia_inverso(palavra):
    inverso = ''
    i = len(palavra) - 1
    while i >= 0:
        inverso += palavra[i]
        i -= 1
    return inverso


def marca_ocorrencia_horizontal(palavra, A, B, m, n, i, j):
    pos = []
    counter = 0
    tamanho = len(palavra)
    for i in range(m):
        for j in range(n):
            if A[i][j] == palavra[counter]:
                counter += 1
                pos.append([i,j])
            if counter == tamanho:
                for posicao in pos:
                    B[i]   


def search_word(A, B, word):
    directions = [[0, 1,], [1, 0], [1, 1], [-1, 0], [0, -1], [-1, -1], [-1, 1], [1, -1]]
    word_length = len(word)
    
    for row in range(len(A)):
        for col in range(len(A[0])):
            for direction in directions:
                dr, dc = direction
                end_row = row + (word_length - 1) * dr
                end_col = col + (word_length - 1) * dc
                
                if 0 <= end_row < len(A) and 0 <= end_col < len(A[0]):
                    temp_row, temp_col = row, col
                    found = True
                    
                    for char in word:
                        if A[temp_row][temp_col] != char:
                            found = False
                            break
                        temp_row += dr
                        temp_col += dc
                    
                    if found:
                        temp_row, temp_col = row, col
                        for char in word:
                            B[temp_row][temp_col] = char
                            temp_row += dr
                            temp_col += dc

dimen = input().split()
m = int(dimen[0])
n = int(dimen[1])
matriz = []

A = le_matriz(matriz, m) # matriz letra
B = cria_matriz_ponto(m, n) # matriz ponto

num_palavras = int(input())
for i in range(num_palavras):
    palavra = input()
    search_word(A, B, palavra)
    print_matriz(B, m, n)
