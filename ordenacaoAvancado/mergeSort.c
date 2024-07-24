#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if ((rand() / (double)RAND_MAX) < 0.5) {
            int j = (int)((n - 1) * (rand() / (double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

void merge(int arr[], int inicio, int meio, int final, int *iteracoes);

void mergeSort(int arr[], int inicio, int final, int *iteracoes){

    if (inicio < final){

        int meio = (inicio + final) / 2;
        mergeSort(arr, inicio, meio, iteracoes);
        mergeSort(arr, meio + 1, final, iteracoes);
        merge(arr, inicio, meio, final, iteracoes);

    }
}

void merge(int arr[], int inicio, int meio, int final, int *iteracoes){

    int com1 = inicio, com2 = meio + 1, comAux = 0;
    int arrAux[final - inicio + 1];

    while(com1 <= meio && com2 <= final){

        (*iteracoes)++;

        if (arr[com1] <= arr[com2]) {
            arrAux[comAux] = arr[com1]; com1++;
        } else {
            arrAux[comAux] = arr[com2]; com2++;
        }
        comAux++;
    }

    while (com1 <= meio) {
        arrAux[comAux] = arr[com1];
        comAux++; com1++;
    }

    while (com2 <= final) {
        arrAux[comAux] = arr[com2];
        comAux++; com2++;
    }

    for (comAux = 0; comAux < final - inicio + 1; comAux++) {
        arr[inicio + comAux] = arrAux[comAux];
    }
}

int main(){
    
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_merge = fopen("MergeSortIteracoesCasoMedio.txt", "w");

    srand(time(0)); // Iniciar os números aleatórios
    // Loop pelos tamanhos de vetor
    for (int i = 0; i < num_tamanhos; i++) {
        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));
        // Preencher o array com valores crescentes
        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }
        // Executar 30 repetições para obter o caso médio
        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;
            // Merge Sort
            mergeSort(arr, 0, tam - 1, &iteracoes);
            fprintf(fp_merge, "%d, ", iteracoes);
        }

        fprintf(fp_merge, "\n");
        free(arr); // Liberar memória do array
    }

    fclose(fp_merge);

    // Pior caso

    FILE *fp_merge_2 = fopen("MergeSortIteracoesPiorCaso.txt", "w");

    for (int i = 0; i < num_tamanhos; i++) {
        int tam2 = tamanhos[i];
        int *arr2 = (int *)malloc(tam2 * sizeof(int));

        for (int j = 0; j < tam2; j++) {
            arr2[j] = tam2 - 1 - j;
        }

        int iteracoes = 0;
        // Merge Sort
        mergeSort(arr2, 0, tam2 - 1, &iteracoes);
        printf("%d ", iteracoes);
        fprintf(fp_merge_2, "%d, ", iteracoes);
        fprintf(fp_merge_2, "\n");

        free(arr2); // Liberar memória do array
    }

    fclose(fp_merge_2);
    return 0;
}
