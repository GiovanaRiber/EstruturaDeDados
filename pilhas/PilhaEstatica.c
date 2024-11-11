#include <stdio.h>
#include <stdlib.h>
#define MAX 5

struct pilha{
    int elemento[MAX];
    int topo;
}; typedef struct pilha Pilha;

Pilha* inicializa(void){ 
    
    Pilha *pi = malloc(sizeof(Pilha));

    if(!pi){
        perror(NULL); exit(1);
    }

    pi->topo = 0; 
    return pi;
}

void insere(Pilha *pi, int val) {

    if(pi->topo == MAX){

        printf("\nPilha cheia!");
        exit(1);
    }

    pi->elemento[pi->topo] = val;
    pi->topo = pi->topo + 1;
}

void remover(Pilha *pi){

    if(pi->topo == 0){

        printf("\nA pilha esta vazia!");
        return;
    }
    
    pi->topo = pi->topo - 1;
}

void destruir(Pilha *pi){

    if(pi != NULL){
        pi->topo = 0;
        free(pi);
    }
}

int tamanho(Pilha *pi){

    return pi->topo;
}

void exibir(Pilha *pi){

    if(pi->topo == 0){

        printf("\nPilha vazia!");
        exit(1);
    }

    printf("\nPILHA\n");
    for(int i = 0; i < pi->topo; i++){

        printf("[%d] ", pi->elemento[i]);
    }
}

int main() {

    Pilha *pi = inicializa();

    insere(pi, 5);
    insere(pi, 6);
    insere(pi, 2);
    insere(pi, 1);

    exibir(pi);

    printf("\nO tamanho da Pilha e %d!", tamanho(pi));

    remover(pi);
    exibir(pi);
    destruir(pi);
    exibir(pi);

    return 0;
}