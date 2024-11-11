#include <stdio.h>
#include <stdlib.h>
#define MAX 5

struct lista {
    int elementos[MAX];
    int ultimo;
}; typedef struct lista lista;

lista* cria(void) {

    lista *f = malloc(sizeof(lista));

    if(!f){
        perror(NULL);
        exit(1);
    }
    f->ultimo = 0;
    return f;
}

void insere_final(lista* f, int a) {

    if(f->ultimo == MAX){

        printf("\nLista cheia!");
        exit(1);
    }
    f->elementos[f->ultimo] = a;
    f->ultimo = f->ultimo + 1;
}

void insere_x(lista* f, int a, int x) {

    if(f->ultimo == MAX){

        printf("\nLista cheia!");
        exit(1);
    }

    for(int i = f->ultimo; i > x; i--){

        f->elementos[i] = f->elementos[i-1];
    }
    f->ultimo = f->ultimo + 1;
    f->elementos[x] = a;
}

int tamanho(lista *f) { return f->ultimo; }

void destroi(lista *p){

    p->ultimo = 0;

    for(int i = 0; i < MAX; i++)
        p->elementos[i] = 0;
}

int recupera(lista *f, int indice){ return f->elementos[indice]; }

void exibe(lista *f){

    if(f->ultimo == 0){

        printf("\nLista vazia!");
        exit(1);
    }

    printf("\n");
    for(int i = 0; i < f->ultimo; i++){

        printf("[%d]", f->elementos[i]);
    }
}

int main() {

    lista *f = cria();

    insere_final(f, 5);
    insere_final(f, 4);
    insere_final(f, 9);
    insere_final(f, 0);

    exibe(f);

    printf("\nO tamanho da Lista e %d!", tamanho(f));

    destroi(f);
    exibe(f);

    return 0;
}