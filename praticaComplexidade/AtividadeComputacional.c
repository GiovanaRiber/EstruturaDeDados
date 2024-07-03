#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Lista{

    int data;
    struct Lista *prox;
}; typedef struct Lista Lista;

Lista *cria_lista(void){ return NULL; }

void libera(Lista *lst){

    Lista* aux = lst;
    Lista* temp;

    while(aux != NULL){

        temp = aux->prox;
        free(aux);
        aux = temp;
    }
}

Lista* insere_ordenado(Lista* lst, int val){

   Lista* novo = (Lista*) malloc(sizeof(Lista));
   Lista* aux = lst;
   Lista* ant = NULL;
   novo->data = val;

    while(aux != NULL && aux->data > val){
        ant = aux;
        aux = aux->prox;
    }

    if(ant == NULL){
        novo->prox = lst;
        lst = novo;
    }else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return lst;
}

int main(){

    int MAX;
    double tempo, timedef;

    FILE *arq;

    arq = fopen("arquivo.txt", "w+");

    for(MAX = 1000; MAX <= 25000; MAX+= 1000){

        for(int j = 0; j < 30; j++){

            Lista* lst = cria_lista();

            tempo = (double)clock();
            tempo = tempo/CLOCKS_PER_SEC;

            for(int i = MAX; i > 0; i--){

                lst = insere_ordenado(lst, i);
            }

            timedef = (((double) clock()) / CLOCKS_PER_SEC) - tempo;
            fprintf(arq, "%lf, ", timedef);
            libera(lst);
        }
        fprintf(arq, "\n");
    }

    return 0;
}