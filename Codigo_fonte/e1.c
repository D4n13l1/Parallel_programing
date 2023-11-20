#include <stdio.h>
#include <omp.h>

int main() {

    FILE *arquivo = fopen("respostas.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int thread_id = 0;
    fprintf(arquivo, "Exercício 1\n\n");
    #pragma omp parallel num_threads(8)
    {
        thread_id = omp_get_thread_num();
        
        fprintf(arquivo, "Thread %d diz: Sou a thread: %d\n", thread_id, thread_id);
    }
    fprintf(arquivo, "\n________________________________\n\n");
    fclose(arquivo);
    return 0;
}
