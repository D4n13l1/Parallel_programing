#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define linha 3840
#define coluna 2160

void preencherMatriz(int** matriz, int valor) {
    double inicio_preenchimento = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j] = valor;
        }
    }

    double fim_preenchimento = omp_get_wtime();
    double duracao_preenchimento = fim_preenchimento - inicio_preenchimento;

    FILE* arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "Tempo de preenchimento de M%d: %f segundos\n", valor, duracao_preenchimento);

    fclose(arquivo);
}

double calcularNormaFrobenius(int** matriz) {
    double inicio_norma = omp_get_wtime();

    double norma = 0.0;

    #pragma omp parallel for reduction(+:norma) collapse(2)
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            norma += pow(matriz[i][j], 2);
        }
    }

    double fim_norma = omp_get_wtime();
    double duracao_norma = fim_norma - inicio_norma;

    FILE* arquivo = fopen("respostas.txt", "a");
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
    FILE* arquivo =  arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    fprintf(arquivo, "Exercicio 5 PARALELO\n");
    fclose(arquivo);
    preencherMatriz(M1, 1);
    preencherMatriz(M2, 2);

    omp_set_num_threads(6);
    double inicio_subtracao = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            M[i][j] = M2[i][j] - M1[i][j];
        }
    }

    double fim_subtracao = omp_get_wtime();
    double duracao_subtracao = fim_subtracao - inicio_subtracao;

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
