#include <stdio.h>
#include <stdlib.h>

int maiorDistancia(float *vet, float media, int n) {

    int x = 0;
    float maior = 0, dist;

    for(int i = 0; i < n; i++){

        dist = (vet[i] - media);

        if(dist > maior){
            maior = dist;
            x = i;

        }
    }

    return x;

}

int main() {

    int n;
    float soma = 0, media;

    printf("Informe um valor inteiro: ");
    scanf("%d", &n);

    float *vet = (float*) malloc(n * sizeof(float));

    if (vet == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    for(int i = 0; i < n; i++){

        printf("Peso pessoa %d: ", i+1);
        scanf("%f", &vet[i]);

        soma += vet[i];
    }

    media = soma/n;

    int indice = maiorDistancia(vet, media, n);

    printf("\nO peso mais distante da media [%.2f] e %.2f !", media, vet[indice]);

    free(vet);

    return 0;
}