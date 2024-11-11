#include <stdio.h>
#include <stdlib.h>

struct Elemento{
    int num;
    struct Elemento *prox;
};
typedef struct Elemento Elemento;

struct Pilha{
    Elemento *topo;
}; typedef struct Pilha Pilha;

Elemento *aux;

Pilha* cria_Pilha(){

    Pilha *pi = (Pilha*) malloc(sizeof(Pilha));

    if(pi != NULL)
        pi->topo = NULL;
    
    return pi;
}

void cadastrar(Pilha *pi, int val){

    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));

    novo->num = val;
    novo->prox = pi->topo;
    pi->topo = novo;
}

void pares(Pilha *pi){

    aux = pi->topo;
    int cont = 0;

    while(aux != NULL) {

        if(aux->num % 2 == 0) {

            printf("[%d] ", aux->num);
            cont++;
        } 

        aux = aux->prox;
    }

    if(cont == 0)
        printf("\nNao ha valores pares na pilha!");

    printf("\n");
}

void remover(Pilha *pi){

    if(pi->topo == NULL) {
        printf("\nPilha VAZIA!");

    } else {

        aux = pi->topo;

        printf("\n%d removido!", pi->topo->num);

        pi->topo = pi->topo->prox;
        free(aux);
    }
}

int main(){

    Pilha *pi = cria_Pilha();
    int codigo;
    int num;

    do{

        printf("============MENU===========");
        printf("\n[1] Cadastrar numero!");
        printf("\n[2] Mostrar numeros pares!");
        printf("\n[3]Excluir numero!");
        printf("\n[4] Sair!");
        printf("\n==========================\n");

        printf("\nEscolha: ");
        scanf("%d", &codigo);

        switch (codigo) {

        case 1:
        
        printf("\nInsira um valor inteiro: ");
        scanf("%d", &num);

        cadastrar(pi, num); break;

        case 2:

        pares(pi); break;

        case 3:

            remover(pi); break;

        case 4:

            break;

        default:

            printf("\nOpcao invalida!\n");
            break;
        }

    }while(codigo != 4);

    return 0;
}