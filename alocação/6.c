#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Imc{

    int idade;
    float peso;
    float altura;
    float imc;

};

int main(){

    int n;

    printf("Informe a quantidade de pessoas: ");
    scanf("%d", &n);

    struct Imc *x = (struct Imc*) calloc(n, sizeof(struct Imc));

    if (x == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    for(int i = 0; i < n; i++){

        printf("\nPessoa %d", i+1);
        printf("\nInforme a idade: ");
        scanf("%d", &x[i].idade);
        printf("Informe o peso: ");
        scanf("%f", &x[i].peso);
        printf("Informe a altura: ");
        scanf("%f", &x[i].altura);

        x[i].imc = x[i].peso/pow(x[i].altura,2);
    }

    printf("\nRESULTADO\n");
    for(int i = 0; i < n; i++){

        printf("\nPessoa %d", i+1);
        printf("\nIdade: %d", x[i].idade);
        printf("\nPeso: %.2f", x[i].peso);
        printf("\nAltura: %.2f", x[i].altura);
        printf("\nIMC: %.2f\n", x[i].imc);
    }


    free(x);
    return 0;
}