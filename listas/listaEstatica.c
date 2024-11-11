#include <stdio.h>
#include <stdlib.h>

#define MAX 6

struct Lista{
    int Elemento[MAX];
    int ultimo;
}; typedef struct Lista Lista;

Lista* cria(void) {

    Lista *p = malloc(sizeof(Lista));

    if(!p){
        
        perror(NULL);
        exit(1);
    }
    p->ultimo = 0;
    return p;
}

void insere_final(Lista* p, int val) {

    if(p->ultimo == MAX){

        printf("\nLista cheia!");
        exit(1);
    }
    p->Elemento[p->ultimo] = val;
    p->ultimo = p->ultimo + 1;
}

void insere_posicao(Lista* p, int val, int indice) {

    if(p->ultimo == MAX){

        printf("\nLista cheia");
        exit(1);
    }

    for(int i = p->ultimo; i > indice; i--)
        p->Elemento[i] = p->Elemento[i-1];
   
    p->Elemento[indice] = val;
    p->ultimo = p->ultimo + 1;
}

int tamanho(Lista *p) { return p->ultimo; }

void destroi(Lista *p) {
    
    if (p != NULL) {

        p->ultimo = 0;
        free(p);
    }
}

void exibe(Lista *p) {

    if(p->ultimo == 0){

        printf("\nLista vazia!");
        exit(1);
    }

    printf("\nLISTA\n");
    for(int i = 0; i < p->ultimo; i++){
        printf("[%d] ", p->Elemento[i]);
    }
}


int main() {

    Lista *p = cria();

    insere_final(p, 5);
    insere_final(p, 3);
    insere_final(p, 1);

    exibe(p);

    insere_posicao(p, 7, 2);

    exibe(p);

    printf("\nO tamanho da lista e %d!", tamanho(p));

    exibe(p);
    destroi(p);
    exibe(p);

    return 0;
}