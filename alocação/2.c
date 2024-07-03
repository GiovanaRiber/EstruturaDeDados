#include <stdio.h> 
#include <stdlib.h>

struct pressao{

    float peso;
    float area;
    float press;

};

int main() {

    int n;

    printf("Quantos objetos serao calculados?: ");
    scanf("%d", &n);

    struct pressao *x = (struct pressao *) calloc(n, sizeof(struct pressao)); 

    if (x == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    for(int i = 0; i < n; i++){
        printf("\nPeso %d: ", i+1);
        scanf("%f", &x[i].peso);
        printf("Area %d: ", i+1);
        scanf("%f", &x[i].area);

        x[i].press = (x[i].peso/x[i].area);
    }

    printf("\nPRESSAO DOS OBJETOS\n");

    for(int i = 0; i < n; i++){
        printf("\nObjeto %d: %.2f", i+1, x[i].press);
    }

    free(x);

    return 0;
}