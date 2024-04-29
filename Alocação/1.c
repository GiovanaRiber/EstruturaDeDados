#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14

struct calculo{

    float raio;
    float area;
    float circunferencia;

};

int main(){

    int n;

    printf("Informe um valor inteiro: ");
    scanf("%d", &n);

    struct calculo *c = (struct calculo*) malloc(n * sizeof(struct calculo));

    if (c == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    for(int i = 0; i < n; i++) {

        printf("\nRaio do circulo %d: ", i+1);
        scanf("%f", &c[i].raio);

        c[i].circunferencia = 2 * pi * c[i].raio;
        c[i].area = pi * pow(c[i].raio,2);
    }

    printf("\nRESULTADO\n");
    for(int i = 0; i < n; i++){

        printf("\nCirculo %d", i+1);
        printf("\nCircunferencia: %.2f ", c[i].circunferencia);
        printf("\nArea: %.2f\n", c[i].area);

    }

    free(c);

    return 0;
}