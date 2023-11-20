#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000000

int main() {
    int *vetor6 = malloc(N * sizeof(int));
    double inicio = omp_get_wtime();
    omp_set_num_threads(6);
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vetor6[i] = 1;
    }
    double fim = omp_get_wtime();
    double duracao = fim - inicio;
    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(arquivo, "Exercicio 3 PARALELO COM 6 THREADS\nTamanho dos vetor: %d\n\n", N);
    fprintf(arquivo, "Tempo de duração: %f segundos\n", duracao);
    fprintf(arquivo, "\n________________________________\n\n");
    fclose(arquivo);
    free(vetor6);

    return 0;
}
