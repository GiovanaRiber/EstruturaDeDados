#include <stdio.h>
#include <stdlib.h>

struct Elemento {
    int num;
    struct Elemento *prox;
};
typedef struct Elemento Elemento;

struct Fila {
    struct Elemento *inicio;
    struct Elemento *fim;
};
typedef struct Fila Fila;

Elemento *aux;

Fila* cria_fila() {

    Fila* fi = (Fila*) malloc(sizeof(Fila));

    if (fi != NULL){
        fi->fim = NULL;
        fi->inicio = NULL;
    }
    return fi;
}

void insere_elemento(Fila *fi) {

    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));

    printf("\nDigite o valor a ser inserido na fila: ");
    scanf("%d", &novo->num);

    novo->prox = NULL;

    if (fi->inicio == NULL) {

        fi->inicio = novo;
        fi->fim = novo;
    } else {

        fi->fim->prox = novo;
        fi->fim = novo;
    }
    printf("\nNumero inserido da fila!");
}

void consulta_fila(Fila *fi) {

    if(fi->inicio == NULL) {

        printf("\nFila VAZIA!");
    } else  {

        aux = fi->inicio;
        do {

            printf("\n%d", aux->num);
            aux = aux->prox;
        }while(aux != NULL);
    }
}

void remove_elemento(Fila *fi) {

    if(fi->inicio == NULL) {

        printf("\nFila Vazia!!");
    } else {

        aux = fi->inicio;
        printf("\n%d removido!", fi->inicio->num);
        fi->inicio = fi->inicio->prox;
        free(aux);
    }
}

void esvazia_fila(Fila *fi) {

    if(fi->inicio ==  NULL){

        printf("\nFila VAZIA!");
    } else {

        aux = fi->inicio;
        do {

            fi->inicio = fi->inicio->prox;
            free(aux);
            aux = fi->inicio;
        }while(aux != NULL);

        printf("\nFila ESVAZIADA!");
    }
}

int main() {

    Fila *fi = cria_fila();

    insere_elemento(fi);
    insere_elemento(fi);
    insere_elemento(fi);

    consulta_fila(fi);
    remove_elemento(fi);

    return 0;
}