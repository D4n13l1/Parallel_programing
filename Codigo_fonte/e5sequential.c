#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define linha 3840
#define coluna 2160

void preencherMatriz(int** matriz, int valor) {
    clock_t inicio_preenchimento = clock();

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j] = valor;
        }
    }

    clock_t fim_preenchimento = clock();
    double duracao_preenchimento = (double)(fim_preenchimento - inicio_preenchimento) / CLOCKS_PER_SEC;

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "Tempo de preenchimento: %f segundos\n", duracao_preenchimento);

    fclose(arquivo);
}

double calcularNormaFrobenius(int** matriz) {
    clock_t inicio_norma = clock();

    double norma = 0.0;

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            norma += pow(matriz[i][j], 2);
        }
    }

    clock_t fim_norma = clock();
    double duracao_norma = (double)(fim_norma - inicio_norma) / CLOCKS_PER_SEC;

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "Tempo de cálculo da norma: %f segundos\n", duracao_norma);

    fclose(arquivo);

    return sqrt(norma);
}

int main() {
    int** M1 = (int**)malloc(linha * sizeof(int*));
    int** M2 = (int**)malloc(linha * sizeof(int*));
    int** M = (int**)malloc(linha * sizeof(int*));

    for (int i = 0; i < linha; i++) {
        M1[i] = (int*)malloc(coluna * sizeof(int));
        M2[i] = (int*)malloc(coluna * sizeof(int));
        M[i] = (int*)malloc(coluna * sizeof(int));
    }

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    fprintf(arquivo, "Exercicio 5 SEQUENCIAL\n");
    fclose(arquivo);
    
    preencherMatriz(M1, 1);
    preencherMatriz(M2, 2);

    clock_t inicio_subtracao = clock();

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            M[i][j] = M2[i][j] - M1[i][j];
        }
    }

    clock_t fim_subtracao = clock();
    double duracao_subtracao = (double)(fim_subtracao - inicio_subtracao) / CLOCKS_PER_SEC;

    arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "Tempo de cálculo da subtração: %f segundos\n", duracao_subtracao);

    fclose(arquivo);

    double normaM = calcularNormaFrobenius(M);

    arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "Norma de Frobenius de M: %f\n", normaM);
    fprintf(arquivo, "\n________________________________\n\n");

    fclose(arquivo);

    // Liberar a memória alocada
    for (int i = 0; i < linha; i++) {
        free(M1[i]);
        free(M2[i]);
        free(M[i]);
    }
    free(M1);
    free(M2);
    free(M);

    return 0;
}
