#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "conjuntos.h"

struct set {
    Elemento elem;
    Set* prox;
};

void add(Set** set, int valor) {

    Set* novo = (Set*) malloc(sizeof(Set));
    if (novo == NULL) { printf("Erro ao alocar memoria!\n"); exit(1); }

    novo->elem.info = valor;
    novo->prox = *set;
    *set = novo;
}

bool isEmpty(Set* set) { return (set == NULL); }

int len(Set* set) {

    int tam = 0;
    while (set != NULL) {
        tam++;
        set = set->prox;
    }
    return tam;
}

bool isIn(Set* set, int valor) {

    while (set != NULL) {
        if (set->elem.info == valor)
            return true;

        set = set->prox;
    }
    return false;
}

bool isNotIn(Set* set, int valor) {

    while (set != NULL) {
        if (set->elem.info == valor)
            return false;

        set = set->prox;
    }
    return true;
}

bool isDisjoint(Set* set1, Set* set2) {

    Set* temp = set2;

    while (set1 != NULL) {
        set2 = temp;
        while (set2 != NULL) {
            if (set1->elem.info == set2->elem.info)
                return false;

            set2 = set2->prox;
        }
        set1 = set1->prox;
    }
    return true;
}

void printSet(Set* set) {

    Set* temp = set;

    while (temp != NULL) {
        printf("[%d]", temp->elem.info);
        temp = temp->prox;
    }
}

void removeElem(Set** set, int valor) {

    Set* ant = NULL;
    Set* s = *set;

    while (s != NULL && s->elem.info != valor) {
        ant = s;
        s = s->prox;
    }

    if (s == NULL)
        return;

    if (ant == NULL)
        *set = s->prox;
    else
        ant->prox = s->prox;

    free(s);
}

void clearConj(Set** set) {

    Set* s = *set;
    Set* temp;

    while (s != NULL) {
        temp = s->prox;
        free(s);
        s = temp;

    }
    *set = NULL;
}

Set* unionConj(Set* set1, Set* set2) {

    Set* set3 = NULL;

    while (set1 != NULL) {
        if (isNotIn(set3, set1->elem.info))
            add(&set3, set1->elem.info);

        set1 = set1->prox;
    }

    while (set2 != NULL) {
        if (isNotIn(set3, set2->elem.info))
            add(&set3, set2->elem.info);

        set2 = set2->prox;
    }

    return set3;
}

Set* intersection(Set* set1, Set* set2) {

    Set* set3 = NULL;
    Set* temp = set2;

    while (set1 != NULL) {
        set2 = temp;
        while (set2 != NULL) {
            if (set1->elem.info == set2->elem.info) {
                if (isNotIn(set3, set1->elem.info))
                    add(&set3, set1->elem.info);
            }
            set2 = set2->prox;
        }
        set1 = set1->prox;
    }
    return set3;
}

Set* difference(Set* set1, Set* set2) {

    Set* set3 = NULL;

    while (set1 != NULL) {
        if (isNotIn(set2, set1->elem.info)) {
            if (isNotIn(set3, set1->elem.info))
                add(&set3, set1->elem.info);
        }
        set1 = set1->prox;
    }
    return set3;
}

Set* symmetric_difference(Set* set1, Set* set2) {

    Set* diff1 = difference(set1, set2);
    Set* diff2 = difference(set2, set1);

    Set* set3 = unionConj(diff1, diff2);

    clearConj(&diff1);
    clearConj(&diff2);

    return set3;
}

bool isSubSet(Set* set1, Set* set2) {

    while (set1 != NULL) {
        if (isNotIn(set2, set1->elem.info))
            return false;

        set1 = set1->prox;
    }
    return true;
}

bool isSuperSet(Set* set1, Set* set2) {

    return isSubSet(set2, set1);
}

void copyConj(Set* set1, Set** set2) {

    while (*set2 != NULL) {
        Set* temp = *set2;
        *set2 = (*set2)->prox;
        free(temp);
    }

    while (set1 != NULL) {
        add(set2, set1->elem.info);
        set1 = set1->prox;
    }
}

Elemento pop(Set** set) {

    if (isEmpty(*set)) {
        printf("\nConjunto vazio\n");
        Elemento x = {0};
        return x;
    }

    int tam = len(*set);
    Set* atual = *set;
    Set* ant = NULL;

    srand((unsigned int)time(NULL));
    int indice = rand() % tam;

    for (int i = 0; i < indice; i++) {
        ant = atual;
        atual = atual->prox;
    }

    Elemento r = atual->elem;

    if (ant == NULL)
        *set = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
    return r;
}
