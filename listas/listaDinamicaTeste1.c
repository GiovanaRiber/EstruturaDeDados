#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista* prox;
};
typedef struct lista Lista;


Lista* lst_cria(void){ // Retorna uma lista vazia
    return NULL;
}

Lista* lst_insere (Lista* lst, int val) {

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = val;
    novo->prox = lst;
    return novo; // Retorna a lista atualizada
}

void lst_imprime (Lista* lst) { // Imprime valores dos elementos

    Lista* p;
    for(p = lst; p != NULL; p = p->prox){

        printf("Info = %d\n", p->info);
    }
}

int lst_vazia (Lista* lst) {

    return (lst == NULL);// Retorna 1 se vazia ou 0 se não vazia
}

int lst_busca (Lista* lst, int v) {

    Lista* p;
    int cont = 0;
    for (p = lst; p != NULL; p = p->prox) {

        if (p->info == v)
            cont++;
    }
    if (cont == 1)
        return cont;
    else
        return cont;
}

Lista* lst_retira (Lista* lst, int val) {

    Lista* ant = NULL;
    Lista* p = lst;

    while (p != NULL && p->info != val) {

        ant = p;
        p = p->prox;
    }

    if (p == NULL)
        return lst;

    if(ant == NULL)
        lst = p->prox;
    else
        ant->prox = p->prox;

    free(p);
    return lst;
}

void lst_libera (Lista* lst) {

    Lista* t;
    Lista* p = lst;

    while (p != NULL) {

        t = p->prox;
        free(p);
        p = t;
    }
}

Lista* lst_insere_ordenado (Lista* lst, int val) {

    Lista* novo;
    Lista* ant = NULL;
    Lista* p = lst;

    while (p != NULL && p->info < val) { // Inserir elementos em ordem

        ant = p;
        p = p->prox;
    }

    novo = (Lista*) malloc(sizeof(Lista));
    novo->info = val;

    if (ant == NULL) {

        novo->prox = lst;
        lst = novo;
    } else {

        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return lst;
}

Lista* lst_insere_final(Lista* lst, int val) {

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    Lista* ant = NULL;
    Lista* p = lst;
    novo->info = val;

    for(p = lst; p != NULL; p = p->prox)
        ant = p;

    novo->prox = NULL;
    ant->prox = novo;

    return lst;
}

Lista* lst_inverte(Lista* lst) {

    Lista* novo = (Lista*) malloc(sizeof(Lista));
    Lista* p = lst;

    while (p != NULL) {

        novo->prox = p;
        p = p->prox;
    }

    return novo;
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

int lst_quantidade (Lista* lst) {

    Lista* p = lst;
    int cont = 0;

    for (p = lst; p != NULL; p = p->prox)
        cont++;
    return cont;
}

int main() {

    Lista* lst;
    Lista* lst1;
    lst = lst_cria();
    lst1 = lst_cria();

    lst = lst_insere(lst, 7);
    lst = lst_insere(lst, 2);
    lst = lst_insere(lst, 5);
    lst = lst_insere(lst, 4);

    lst1 = lst_insere(lst1, 63);
    lst1 = lst_insere(lst1, 43);
    lst1 = lst_insere(lst1, 23);
    lst1 = lst_insere(lst1, 83);

    lst_imprime(lst);

    if (lst_busca(lst, 10) == 1)
        printf("\nElemento encontrado\n");
    else
        printf("Elemento nao encontrado\n");

    lst = lst_retira(lst, 83);
    printf("\n");
    lst_imprime(lst);

    lst = lst_insere_ordenado(lst, 52);
    printf("\n");
    lst_imprime(lst);

    printf("\n%d", lst_igual(lst, lst1));

    printf("\nExistem %d elementos na lista!", lst_quantidade(lst));

    lst = lst_insere_final(lst, 103);
    printf("\nInsere elemento no final\n");
    lst_imprime(lst);

    lst = lst_inverte(lst);
    printf("\nInverter\n");
    lst_imprime(lst);

    lst_libera(lst);
    lst_libera(lst1);

    return 0;
}
