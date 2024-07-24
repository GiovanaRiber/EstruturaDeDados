#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor(int arr[], int n){

    for(int i = 0; i < n; i ++){

        if((rand()/(double)RAND_MAX) < 0.5){

            int j = (int)((n -1)*(rand()/(double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

void selectionSort(int arr[] ,int n ,int * iteracoes){

    *iteracoes = 0;
    for(int i = 0; i < n-1; i++){

        int min_idx = i;

        for(int j = i + 1; j < n; j++){

            (*iteracoes)++;

            if(arr[j] < arr [min_idx]){
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main(){

    int tamanhos [] = {5000 , 10000 , 15000 , 20000 , 25000 , 30000 ,
    35000 , 40000 , 45000 , 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof (tamanhos[0]) ;

    FILE * fp_selection = fopen("SelectionSortIteracoesCasoMedio.txt", "w");

    srand(time(0));

    for(int i = 0; i < num_tamanhos; i ++){

        int tam = tamanhos[i];

        int * arr = (int*) malloc(tam * sizeof (int));
       
        for(int j = 0; j < tam ; j ++){
            arr [j] = j;
        }
      
        for(int j = 0; j < 30; j ++){

            mistureVetor(arr, tam);
            int iteracoes;
     
            selectionSort(arr, tam, &iteracoes);
            fprintf(fp_selection, "%d, ",iteracoes);
        }

        fprintf(fp_selection, "\n");
        free (arr); 
    }

    fclose(fp_selection);

    //pior caso

    FILE * fp_selection_2 = fopen ("SelectionSortIteracoesPiorCaso.txt", "w");

    srand (time(0));

    for(int i = 0; i < num_tamanhos ; i ++){

        int tam2 = tamanhos[i];

        int * arr2 = (int *) malloc (tam2 * sizeof (int));
   
        for(int j = 0; j < tam2; j ++){

            arr2[j] = tam2 - 1 - j;
        }

        int iteracoes;
   
        //selection Sort
        selectionSort(arr2, tam2 , &iteracoes);
        fprintf(fp_selection_2, "%d, ", iteracoes);
        fprintf(fp_selection_2, "\n");

        free(arr2); // Liberar memoria do array
    }

    fclose (fp_selection_2);

    return 0;
}