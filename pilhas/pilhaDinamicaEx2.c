#include <stdio.h>
#include <stdlib.h>

struct Elemento{
    int num;
    struct Elemento *prox;
};
typedef struct Elemento Elemento;

struct Pilha{

    Elemento *topo;
};
typedef struct Pilha Pilha;

Elemento *aux;

Pilha* cria_Pilha(){

    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL) {

        pi->topo = NULL;
    }
    return pi;
}

void insere(Pilha *pi, int val) {

    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));

    novo->num = val;

    novo->prox = pi->topo;

    pi->topo = novo;
}

void exibir(Pilha *pi){

    aux = pi->topo;

    if(pi->topo == NULL){

        printf("\nPilha vazia!");
        return;
    }

    while(aux != NULL) {

        printf("[%d] ", aux->num);

        aux = aux->prox;
    }

}

int main() {

    Pilha *pi = cria_Pilha();
    int num;

    printf("\nValor inteiro: ");
    scanf("%d", &num);

    int x = 0, y = 1, z;

    printf("\nSequencia Fibonacci\n");
    for(int i = 0; i < num; i++){

        z = x + y;
        x = y;
        y = z;
        insere(pi, z);
    }
    exibir(pi);

}