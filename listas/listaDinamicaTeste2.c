#include <stdio.h>
#include <stdlib.h>

struct Lista{
    int info;
    struct Lista *prox;
};
typedef struct Lista Lista;

Lista* cria(void){

    return NULL;
}

Lista* insere_Elemento(Lista* lst, int val){

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = val;

    novo->prox = lst;
    return novo;
}

void exibe(Lista* lst) {

    if(lst == NULL){

        printf("\nLista vazia!");
        return;
    }

    printf("\nLista\n");
    printf("-------------------\n");
    while(lst != NULL){

        printf("[%d]", lst->info);
        lst = lst->prox;
    }
}

Lista* remove_elemento(Lista* lst, int val){

    Lista* aux = lst;
    Lista* ant = NULL;

    while(aux != NULL && aux->info != val){

        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL){
        printf("\n%d nao encontrado na lista!", val);
        return lst;
    }

    if(ant == NULL)
        lst = aux->prox;
        
    else
        ant->prox = aux->prox;
    
    free(aux);
    
    return lst;
}

int busca(Lista* lst, int x){

    int cont = 0;

    while(lst != NULL){

        if(lst->info == x)
            cont = 1;
        lst = lst->prox;
    }
    return cont;
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

void limpar(Lista* lst) {

    Lista* t = NULL;
    Lista* p = lst;

    while(p != NULL){

        t = p->prox;
        free(p);
        p = t;
    }
}

int lst_quantidade (Lista* lst) {

    Lista* p = lst;
    int cont = 0;

    for (p = lst; p != NULL; p = p->prox)
        cont++;

    return cont;
}

void par_impar(Lista* lst) {

    Lista* aux = lst;
    int par = 0;
    int impar = 0;

    while(aux != NULL){

        if(aux->info % 2 == 0){
            par++;
        } else {
            impar++;
        }
        aux = aux->prox;
    }

    printf("\n%d numeros pares!", par);
    printf("\n%d numeros impares!", impar);

}

int main() {

    Lista* lst = cria();

    lst = insere_Elemento(lst, 5);
    lst = insere_Elemento(lst, 3);
    lst = insere_Elemento(lst, 1);
    lst = insere_Elemento(lst, 2);
    lst = insere_Elemento(lst, 8);
    lst = insere_Elemento(lst, 2);

    exibe(lst);

    int x = busca(lst, 2);
    if(x == 1)
        printf("\nElemento encontrado na lista!");
    else
        printf("\nElemento não encontrado na lista!");

    lst = remove_elemento(lst, 2);
    
    lst = inverter(lst);
    exibe(lst);

    par_impar(lst);

    return 0;
}