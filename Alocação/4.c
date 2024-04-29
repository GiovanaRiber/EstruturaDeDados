#include <stdio.h>
#include <stdlib.h>

struct provas{

    float nota1;
    float nota2;
    float nota3;
    float media;
};

int main(){

    int n;
    float soma = 0;

    printf("Informe a quantidade de alunos: ");
    scanf("%d", &n);

    struct provas *x = (struct provas*) calloc(n, sizeof(struct provas));

    if (x == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    for(int i = 0; i < n; i++){

        printf("\nAluno %d", i+1);
        printf("\nNota 1: ");
        scanf("%f", &x[i].nota1);
        printf("Nota2: ");
        scanf("%f", &x[i].nota2);
        printf("Nota 3: ");
        scanf("%f", &x[i].nota3);

        soma += x[i].nota1 + x[i].nota2 + x[i].nota3;

        x[i].media = soma/n;

        soma = 0;
    }

    float maiorNota = 0;
    int indice = 0, i;

    for(i = 0; i < n; i++){

        if(x[i].media > maiorNota){

            maiorNota = x[i].media;
            indice = i;

        }
    }

    printf("\nA maior nota entre os alunos e %.2f do aluno %d!", maiorNota, indice+1);


    free(x);
    return 0;
}