#include <stdio.h>
#include <stdlib.h>
#define MAX 5

struct fila{

    int elemento[MAX];
    int final;
    int inicio;
}; typedef struct fila Fila;

Fila* cria(void) {

    Fila *fi = malloc(sizeof(Fila));

    if(!fi){

        perror(NULL); exit(1);
    }

    fi->inicio = 0;
    fi->final = 0;
    return fi;
}

void insere(Fila *f, int val){

    if((f->final + 1 == f->inicio) || (f->final == MAX-1 && f->inicio == 0)){
        printf("\nFila cheia!"); exit(1);
    }
    
    f->elemento[f->final] = val;
    f->final = f->final + 1;

    if(f->final == MAX)
        f->final = 0;
}

void remover(Fila *f) {

    if(f->final == f->inicio){
        printf("\nFila vazia"); exit(1);
    }

    f->inicio = f->inicio + 1;

    if(f->final == MAX)
        f->final = 0;
}

int tamanho(Fila *f){

    int tam = f->final - f->inicio;

    if(tam < 0)
        tam = tam + MAX;

    return tam;
}

void exibir(Fila *f){

    if(f->final == f->inicio){
        printf("\nFila vazia"); exit(1);
    }

    printf("\nFILA\n");
    int i = f->inicio;

    while(i != f->final){

        printf("[%d] ", f->elemento[i]);
        i = (i + 1) % MAX;
    }
}

void destroi(Fila *f){

    if(f->final == f->inicio){
        printf("\nFila Vazia!"); exit(1);
    }

    f->inicio = 0;
    f->final = 0;
    free(f);
}

int main(){

    Fila *f = cria();

    insere(f, 5);
    insere(f, 3);
    insere(f, 8);
    insere(f, 1);

    exibir(f);
    remover(f);
    exibir(f);
    
    printf("\nO tamanho da Fila e %d!", tamanho(f));

    destroi(f);
    exibir(f);

    return 0;
}