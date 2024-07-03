#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int cont = 0;

int geraPosRandomBusca(int tam) {
    return (int)((tam-1)*((double)rand()/RAND_MAX));
}

int buscaLinear(int *v, int n, int elem){

    for(int i = 0; i < n; i++){

        cont++;
        if(v[i] == elem){
            return i;
        }
    }
    return -1;
}

int main(){

    int max;

    srand(time(0));

    FILE *arq1;
    arq1 = fopen("interacoesCasoMedioLinear.txt", "w+");

    for(max = 5000; max <= 50000; max += 5000){

        for(int j = 0; j < 30; j++){

            int vet[max];
            int pos = geraPosRandomBusca(max);

            for(int i = max; i > 0; i--){

                vet[i-1] = i-1;
            }
            buscaLinear(vet, max, pos);
            fprintf(arq1, "%d, ", cont);
            cont = 0;
        }
        fprintf(arq1, "\n");
    }
    fclose(arq1);

    FILE *arq2;
    arq2 = fopen("iteracoesPiorCasoLinear.txt", "w+");

    for(max = 5000; max <= 50000; max += 5000){

        int vet[max];
        for(int i = max; i > 0; i--){
            vet[i-1] = i-1;
        }
        buscaLinear(vet, max, max+1);
        fprintf(arq2, "%d, ", cont);
        cont = 0;

        fprintf(arq2, "\n");
    }
    fclose(arq2);

    return 0;
}