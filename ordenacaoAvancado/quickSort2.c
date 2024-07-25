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

int particiona(int arr[], int inicio, int final, int *iteracoes);

void quickSortRandomizado(int arr[], int inicio, int final, int *iteracoes) {
    if (inicio < final) {
        // Escolhe um pivô aleatório
        int pivoAleatorio = inicio + rand() % (final - inicio + 1);

        int temp = arr[pivoAleatorio];
        arr[pivoAleatorio] = arr[final];
        arr[final] = temp;

        int pivo = particiona(arr, inicio, final, iteracoes);
        quickSortRandomizado(arr, inicio, pivo - 1, iteracoes);
        quickSortRandomizado(arr, pivo + 1, final, iteracoes);
    }
}

int particiona(int arr[], int inicio, int final, int *iteracoes){

    int pivo = arr[final];
    int pivo_indice = inicio;

    for(int i = inicio; i < final; i++){

        (*iteracoes)++; 

        if(arr[i] <= pivo){

            int aux = arr[i];
            arr[i] = arr[pivo_indice];
            arr[pivo_indice] = aux;
            pivo_indice++;
        }
    }

    int aux = arr[pivo_indice];
    arr[pivo_indice] = arr[final];
    arr[final] = aux;

    return pivo_indice;
}

int main(){

    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *fp_quick = fopen("QuickSortRandomizadoIteracoesCasoMedio.txt", "w");

    srand(time(0));

    // Loop pelos tamanhos de vetor
    for(int i = 0; i < num_tamanhos; i++){

        int tam = tamanhos[i];
        int *arr = (int *)malloc(tam * sizeof(int));

        for (int j = 0; j < tam; j++) {
            arr[j] = j;
        }

        for (int j = 0; j < 30; j++) {
            mistureVetor(arr, tam);
            int iteracoes = 0;
            quickSortRandomizado(arr, 0, tam - 1, &iteracoes); 
            fprintf(fp_quick, "%d, ", iteracoes); 
        }
        fprintf(fp_quick, "\n");
        free(arr);
    }

    fclose(fp_quick);

    //Pior caso
    FILE *fp_quick_2 = fopen("QuickSortRandomizadoIteracoesPiorCaso.txt", "w");

    for(int i = 0; i < num_tamanhos; i++){

        int tam2 = tamanhos[i];
        int *arr2 = (int *)malloc(tam2 * sizeof(int));

        for (int j = 0; j < tam2; j++){
            
            arr2[j] = tam2 - 1 - j;
        }

        int iteracoes = 0;
        quickSortRandomizado(arr2, 0, tam2 - 1, &iteracoes);
        fprintf(fp_quick_2, "%d, ", iteracoes);
        fprintf(fp_quick_2, "\n");

        free(arr2);
    }

    fclose(fp_quick_2);

    return 0;
}
