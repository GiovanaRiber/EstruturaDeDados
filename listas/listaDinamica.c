#include <stdio.h>
#include <stdlib.h>

struct lista{
    int info;
    struct lista* prox;

};
typedef struct lista Lista;

Lista* cria_lista(void){

    return NULL;
}

Lista* insere_elemento_inicio(Lista* lst){

    Lista* novo = (Lista*) malloc(sizeof(Lista));

    printf("Elemento: ");
    scanf("%d", &novo->info);

    novo->prox = lst;

    return novo;
}

Lista* insere_ordenado(Lista* lst) {

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    Lista* ant = NULL;
    Lista* p = lst;

    int x;

    printf("\nValor: ");
    scanf("%d", &x);

    while(p != NULL && p->info < x){
        ant = p;
        p = p->prox;
    }

    novo->info = x;

    if(ant == NULL){

        novo->prox = lst;
        lst = novo;
    } else {

        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return lst;
}

void exibir(Lista* lst) {

    printf("\n");
    while(lst != NULL) {

        printf("[%d] ", lst->info);
        lst = lst->prox;
    }
}

Lista* remover_elemento(Lista* lst) {

    int x = 2;
    scanf("%d", &x);

    Lista* ant = NULL;
    Lista* p = lst;

    while(p != NULL && p->info != x) {

        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return lst;
    
    if(ant == NULL)
        lst = p->prox;

    else
        ant->prox = p->prox;
    
    free(p);

    return lst;
}

int lst_igual (Lista* lst1, Lista* lst2) {

    Lista* p1;
    Lista* p2;

    for(p1 = lst1, p2 = lst2; p1 != NULL && p2 != NULL;
        p1 = p1->prox, p2 = p2->prox) {

        if(p1->info != p2->info)
            return 0;
    }
    return p1 == p2;
}

Lista* inverter(Lista* lst) {

    Lista* aux = lst;
    Lista* x = NULL;
    Lista* y = NULL;

    while(aux != NULL) {

        y = aux->prox;
        aux->prox = x;
        x = aux;
        aux = y;
    }
    return x;
}

Lista* insere_elemento_final(Lista* lst, int val){

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    Lista* ultimo = NULL;

    novo->info = val;

    while(lst != NULL){

        ultimo = lst;
        lst = lst->prox;
    }

    novo->prox = NULL;
    ultimo->prox = novo;

    return lst;
}

int busca(Lista* lst){

    int x = 2;
    int cont = 0;
    scanf("%d", &x);

    while(lst != NULL) {

        if(lst->info == x)
            cont = 1;

        lst = lst->prox;
    }

    return cont;
}

void liberar(Lista* lst) {

    Lista* t;
    Lista* p = lst;

    while(p != NULL) {

        t = p->prox;
        free(p);
        p = t;
    }
}

int main(){

    Lista* lst;

    lst = cria_lista();
    lst = insere_elemento_inicio(lst);
    lst = insere_elemento_inicio(lst);
    lst = insere_elemento_inicio(lst);

    printf("\nLISTA: ");
    exibir(lst);

    lst = remover(lst);

    printf("\nLISTA: ");
    exibir(lst);

    int x = busca(lst);
    printf("\n");
    if(x == 0)
        printf("\nElemento nao encontrado na lista!");
    else    
        printf("\nElemento encontrado na lista!");

    lst = insere_ordenado(lst);

    printf("\nLISTA: ");
    exibir(lst);

    lst = inverter(lst);
    exibir(lst);

    insere_elemento_final(lst, 9);
    exibir(lst);

    liberar(lst);

    return 0;

}