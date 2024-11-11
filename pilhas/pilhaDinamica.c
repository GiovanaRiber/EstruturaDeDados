#include <stdio.h>
#include <stdlib.h>

struct Elemento {
    int num;
    struct Elemento *prox;
};
typedef struct Elemento Elemento;

struct Pilha{
    Elemento *topo;
}; typedef struct Pilha Pilha;

Elemento *aux1, *aux2;

Pilha* cria_pilha() {

    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL) {
        pi->topo = NULL;
    }
    return pi;
}

void insere_elemento (Pilha *pi, int val) {

    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->num = val;
    novo->prox = pi->topo;

    pi->topo = novo;
}

void exibe(Pilha *pi) {

    if(pi->topo == NULL) {
        printf("\nPilha VAZIA!");

    } else {

        aux1 = pi->topo;
        do {

            printf("[%d] ", aux1->num);
            aux1 = aux1->prox;
        }while(aux1 != NULL);
    }
}

void pilhas_iguais(Pilha *p1, Pilha *p2) {
    
    aux1 = p1->topo;
    aux2 = p2->topo;

    while (aux1 != NULL && aux2 != NULL) {

        if (aux1->num != aux2->num) {

            printf("\nAs pilhas nao sao iguais!");
            return;
        }
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }

    if (aux1 == NULL && aux2 == NULL) {

        printf("\nAs pilhas sao iguais!");
    } else if (aux1 == NULL) {

        printf("\nA Pilha 2 e maior!");
    } else {

        printf("\nA Pilha 1 e maior!");
    }
}

int par(Pilha *pi){

    aux1 = pi->topo;

    int cont = 0;

    while(aux1 != NULL) {

        if(aux1->num % 2 == 0)
            cont++;

        aux1 = aux1->prox;
    }
    return cont;
}

int impar(Pilha *pi){

    aux1 = pi->topo;

    int cont = 0;

    while(aux1 != NULL) {

        if(aux1->num % 2 != 0)
            cont++;

        aux1 = aux1->prox;
    }
    return cont;
}

void calcula(Pilha *pi) {

    aux1 = pi->topo;

    int maior = 0, cont = 0;
    float soma = 0;
    int menor = 100000;

    while(aux1 != NULL){

        if(aux1->num > maior)
            maior = aux1->num;
        
        if(aux1->num < menor)
            menor = aux1->num;
        
        cont++;
        soma += aux1->num;
        aux1 = aux1->prox;
    }

    printf("\nMaior valor da pilha: %d", maior);
    printf("\nMenor valor da pilha: %d", menor);
    printf("\nMedi aritmetica da pilha: %.2f", soma/cont);
}

void transferir(Pilha *p1, Pilha *p2) {

    aux1 = p1->topo;
    aux2 = p2->topo;

    while (aux1 != NULL && aux2 != NULL) {

        aux2->num = aux1->num;
        
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }

    printf("\n");
    exibe(p2);
}

int main(){

    Pilha *p1 = cria_pilha();
    Pilha *p2 = cria_pilha();

    insere_elemento(p1, 2);
    insere_elemento(p1, 5);
    insere_elemento(p1, 3);

    insere_elemento(p2, 4);
    insere_elemento(p2, 5);
    insere_elemento(p2, 9);
    insere_elemento(p2, 7);

    printf("\n\nPilha 1\n");
    exibe(p1);

    printf("\n\nPilha 2\n");

    exibe(p2);
    pilhas_iguais(p1, p2);

    printf("\n\nExiste(m) %d valor(es) par(es) na Pilha!", par(p1));
    printf("\nExiste(m) %d valor(es) impar(es) na Pilha!", impar(p1));

    transferir(p1, p2);
    calcula(p2);

    return 0;
}
