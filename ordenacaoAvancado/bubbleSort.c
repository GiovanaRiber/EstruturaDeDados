#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mistureVetor ( int arr [] , int n ){

    for( int i = 0; i < n; i ++){

        if (( rand () / ( double ) RAND_MAX ) < 0.5){

            int j = ( int ) ((n -1) *( rand () /( double ) RAND_MAX ));
            int temp = arr [i];
            arr [i] = arr [j];
            arr [j] = temp;
        }
    }
}

void bubbleSort(int arr[], int n, int * iteracoes){

    *iteracoes = 0;
    for(int i = 0; i < n-1; i++){

        for(int j = 1; j < n-i; j++){

            (*iteracoes)++;
            if (arr [j] < arr [j-1]){
               int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){

    int tamanhos [] = {5000 , 10000 , 15000 , 20000 , 25000 , 30000 ,
    35000 , 40000 , 45000 , 50000};
    int num_tamanhos = sizeof (tamanhos) / sizeof (tamanhos [0]) ;

    FILE * fp_bubble = fopen ("BubbleSortIteracoesCasoMedio.txt", "w");

    srand (time(0));

    for(int i = 0; i < num_tamanhos ; i ++){

        int tam = tamanhos[i];

        int * arr = (int *) malloc (tam * sizeof (int));
   
        for(int j = 0; j < tam ; j ++){

            arr [j] = j;
        }
       
        for (int j = 0; j < 30; j ++){

            mistureVetor (arr, tam);
            int iteracoes;
            //bubble Sort
            bubbleSort(arr, tam , &iteracoes);
            fprintf(fp_bubble , "%d, ", iteracoes);
        }

        fprintf(fp_bubble, "\n");
        free(arr); // Liberar memoria do array
    }

    fclose (fp_bubble);

    //pior caso

    FILE * fp_bubble_2 = fopen ("BubbleSortIteracoesPiorCaso.txt", "w");

    srand (time(0));

    for(int i = 0; i < num_tamanhos ; i ++){

        int tam2 = tamanhos[i];

        int * arr2 = (int *) malloc (tam2 * sizeof (int));
   
        for(int j = 0; j < tam2; j ++){

            arr2 [j] = tam2 - 1 - j;
        }

        int iteracoes;
   
        //bubble Sort
        bubbleSort(arr2, tam2 , &iteracoes);
        fprintf(fp_bubble_2, "%d, ", iteracoes);
        fprintf(fp_bubble_2, "\n");

        free(arr2); // Liberar memoria do array
    }

    fclose (fp_bubble_2);
    return 0;
}