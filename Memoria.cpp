#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 4
#define TOTAL_PARES 8

void gerarMatriz(int matriz[TAM][TAM]) {
    int pares[16] = {0};
    int usados[10] = {0}; // para evitar mais que dois de cada

    srand(time(NULL));

    // Gera 8 pares (cada número aparece duas vezes)
    int count = 0;
    while (count < TOTAL_PARES) {
        int num = rand() % 10;
        if (usados[num] < 2) {
            pares[count * 2] = num;
            pares[count * 2 + 1] = num;
            usados[num] += 2;
            count++;
        }
    }

    // Embaralha os pares
    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = pares[i];
        pares[i] = pares[j];
        pares[j] = temp;
    }

    // Preenche a matriz 4x4
    int k = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = pares[k++];
        }
    }
}
