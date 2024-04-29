#include <stdio.h>
#include <stdlib.h>



int main(){

    float **matriz;
    int i, j, n;

    printf("Informe a dimensao da matriz: ");
    scanf("%d", &n);

    matriz = (float**) malloc(n * sizeof(float*));

    for(i = 0; i < n; i++){
        matriz[i] = (float*) calloc(n, sizeof(float));
    }

    if(matriz == NULL){
        printf("Erro na alocação de memória.");
        exit(1);
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){

            printf("Informe a distancia da posicao[%d][%d]: ", i, j);
            scanf("%f", &matriz[i][j]);

        }
    }

    printf("\nMATRIZ\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("[%.2f]", matriz[i][j]);
        }
        printf("\n");
    }

    float maiorValor, menorValor;

    maiorValor = matriz[0][0];
    menorValor = 100000;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            
            if(matriz[i][j] < menorValor)
                menorValor = matriz[i][j];

            if(matriz[i][j] > maiorValor)
                maiorValor = matriz[i][j];

        }
    }

    printf("\nMaior valor: %.2f\nMenor Valor: %.2f", maiorValor, menorValor);

    for(i = 0;  i < n; i++){
        for(j = 0; j < n; j++){
            free(matriz[i]);
        }
    }
    free(matriz);






    return 0;
}