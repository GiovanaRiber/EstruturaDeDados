#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para misturar o vetor aleatoriamente
void mistureVetor(int arr[], int n){

    for(int i = 0; i < n; i++){

        if((rand() / (double)RAND_MAX) < 0.5){

            int j = (int)((n - 1) * (rand() / (double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

// Função de particionamento usada pelo Quick Sort
int particiona(int arr[], int inicio, int final, int *iteracoes){

    int pivo = arr[final]; // Escolhe o pivô
    int pivo_indice = inicio;

    for(int i = inicio; i < final; i++){

        (*iteracoes)++; // Conta iterações
        if (arr[i] <= pivo) {
            // Troca elementos
            int aux = arr[i];
            arr[i] = arr[pivo_indice];
            arr[pivo_indice] = aux;
            pivo_indice++;
        }
    }

    // Coloca o pivô na posição correta
    int aux = arr[pivo_indice];
    arr[pivo_indice] = arr[final];
    arr[final] = aux;

    return pivo_indice;
}

// Função principal do Quick Sort
void quickSort(int arr[], int inicio, int final, int *iteracoes){

    if(inicio < final){

        int pivo = particiona(arr, inicio, final, iteracoes);
        quickSort(arr, inicio, pivo - 1, iteracoes);
        quickSort(arr, pivo + 1, final, iteracoes);
    }
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Arquivo para armazenar iterações do caso médio
    FILE *fp_quick = fopen("QuickSortIteracoesCasoMedio.txt", "w");
    if (fp_quick == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo QuickSortIteracoesCasoMedio.txt!\n");
        return 1;
    }

    srand(time(0)); // Inicializa a semente do gerador de números aleatórios

    // Loop pelos tamanhos de vetor
    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o vetor!\n");
            return 1;
        }

        // Preencher o array com valores crescentes
        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }

        // Executar 30 repetições para obter o caso médio
        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam); // Mistura o array
            int iteracoes = 0;
            quickSort(arr, 0, tam - 1, &iteracoes); // Ordena o array
            fprintf(fp_quick, "%d, ", iteracoes); // Armazena o número de iterações
        }
        fprintf(fp_quick, "\n");
        free(arr); // Libera a memória do array
    }

    fclose(fp_quick);

    // Arquivo para armazenar iterações do pior caso
    FILE *fp_quick_2 = fopen("QuickSortIteracoesPiorCaso.txt", "w");
    if (fp_quick_2 == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo QuickSortIteracoesPiorCaso.txt!\n");
        return 1;
    }

    for (int i = 0; i < num_tamanhos; i++) {
        int tam2 = tamanhos[i];
        int *arr2 = (int *)malloc(tam2 * sizeof(int));
        if (arr2 == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o vetor!\n");
            return 1;
        }

        // Preenche o array em ordem decrescente para o pior caso
        for (int j = 0; j < tam2; j++) {
            arr2[j] = tam2 - 1 - j;
        }

        int iteracoes = 0;
        quickSort(arr2, 0, tam2 - 1, &iteracoes); // Ordena o array
        printf("%d\n ", iteracoes);
        fprintf(fp_quick_2, "%d, ", iteracoes);
        fprintf(fp_quick_2, "\n");

        free(arr2); // Libera a memória do array
    }

    fclose(fp_quick_2);

    return 0;
}
