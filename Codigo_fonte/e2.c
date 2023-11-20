#include <stdio.h>
#include <omp.h>

int main() {

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    int thread_id = 0;
    fprintf(arquivo, "Exercicio 2\n\n");
    #pragma omp parallel num_threads(8)
    {
        thread_id = omp_get_thread_num();
        if (thread_id == 0)

        {
            int total_threads = omp_get_num_threads();
            fprintf(arquivo, "Thread %d fez o printf.\nTotal de Threads: %d\n", thread_id, total_threads);
        }
    }
    fprintf(arquivo, "\n________________________________\n\n");
    fclose(arquivo);
    return 0;
}
