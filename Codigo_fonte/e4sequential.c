#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

int main() {
    int *vetor1 = malloc(N * sizeof(int));
    int *vetor2 = malloc(N * sizeof(int));

    double inicio_preenchimento = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        vetor1[i] = 10;
        vetor2[i] = 20;
    }

    double fim_preenchimento = omp_get_wtime();
    
    double duracao_preenchimento = fim_preenchimento - inicio_preenchimento;

    double inicio_produto_interno = omp_get_wtime();

    double produto_interno = 0;
    for (int i = 0; i < N; i++) {
        produto_interno += vetor1[i] * vetor2[i];
    }
    double fim_produto_interno = omp_get_wtime();
    double duracao_produto_interno = fim_produto_interno - inicio_produto_interno;

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(arquivo, "Exercicio 4 SEQUENCIAL\nTAMANHO DO VETOR: %d\n\n", N);
    fprintf(arquivo, "Produto Interno: %f\n", produto_interno);
    fprintf(arquivo, "Tempo de duração do preenchimento: %f segundos\n", duracao_preenchimento);
    fprintf(arquivo, "Tempo de duração do produto interno: %f segundos\n", duracao_produto_interno);
    
    fprintf(arquivo, "\n________________________________\n\n");
    fclose(arquivo);

    free(vetor1);
    free(vetor2);

    return 0;
}
