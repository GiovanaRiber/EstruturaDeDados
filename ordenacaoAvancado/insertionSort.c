#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor ( int arr [] , int n ){

    for ( int i = 0; i < n; i ++){

        if (( rand () / ( double ) RAND_MAX ) < 0.5){

            int j = ( int ) ((n -1) *( rand () /( double ) RAND_MAX ));
            int temp = arr [i];
            arr [i] = arr [j];
            arr [j] = temp;
        }
    }
}

void insertionSort(int arr[] , int n , int * iteracoes){

    *iteracoes = 0;
    int j, i, aux;

    for(i = 1; i < n - 1; i ++){

        aux = arr[i];

        for (j = i; (j > 0) && aux < arr[j-1]; j--){

            (*iteracoes)++;

            arr[j] = arr[j-1];
        }
        arr[j] = aux;
    }
}

int main(){

    int tamanhos [] = {5000 , 10000 , 15000 , 20000 , 25000 , 30000 ,
    35000 , 40000 , 45000 , 50000};
    int num_tamanhos = sizeof (tamanhos) / sizeof (tamanhos [0]) ;

    FILE * fp_insertion = fopen ("InsertionSortIteracoesCasoMedio.txt", "w");

    srand ( time (0) ) ; // Iniciar os numeros aleatorios
    // Loop pelos tamanhos de vetor
    for(int i = 0; i < num_tamanhos ; i ++){

        int tam = tamanhos[i];

        int * arr = (int *) malloc(tam * sizeof (int));
        // Preencher o array com valores crescentes
        for (int j = 0; j < tam ; j ++){
            arr [j ] = j;
        }
        // Executar 30 repeticoes para obter o caso medio
        for (int j = 0; j < 30; j ++){

            mistureVetor (arr, tam);
            int iteracoes = 0;
     
            insertionSort(arr, tam , &iteracoes);
            fprintf(fp_insertion , "%d, ", iteracoes);
        }

        fprintf(fp_insertion, "\n");
        free (arr); // Liberar memoria do array
    }

    fclose (fp_insertion);

    //pior caso

    FILE * fp_insertion_2 = fopen ("InsertionSortIteracoesPiorCaso.txt", "w");

    srand (time(0));

    for(int i = 0; i < num_tamanhos ; i ++){

        int tam2 = tamanhos[i];

        int * arr2 = (int*) malloc(tam2 * sizeof (int));
   
        for(int j = 0; j < tam2; j ++){

            arr2[j] = tam2 - 1 - j;
        }

        int iteracoes = 0;
   
        //insertion Sort
        insertionSort(arr2, tam2 , &iteracoes);
        fprintf(fp_insertion_2, "%d, ", iteracoes);
        fprintf(fp_insertion_2, "\n");

        free(arr2); // Liberar memoria do array
    }

    fclose (fp_insertion_2);
    return 0;
}