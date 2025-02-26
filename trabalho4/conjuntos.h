#ifndef CONJUNTOS_H_INCLUDED
#define CONJUNTOS_H_INCLUDED

#include <stdbool.h>

typedef struct set Set;

typedef struct elemento {
    int info;
} Elemento;

void add(Set** set, int valor);

bool isEmpty(Set* set);

int len(Set* set);

bool isIn(Set* set, int valor);

bool isNotIn(Set* set, int valor);

bool isDisjoint(Set* set1, Set* set2);

void printSet(Set* set);

void removeElem(Set** set, int valor);

void clearConj(Set** set);

Set* unionConj(Set* set1, Set* set2);

Set* intersection(Set* set1, Set* set2);

Set* difference(Set* set1, Set* set2);

Set* symmetric_difference(Set* set1, Set* set2);

bool isSubSet(Set* set1, Set* set2);

bool isSuperSet(Set* set1, Set* set2);

void copyConj(Set* set1, Set** set2);

Elemento pop(Set** set);
#endif // CONJUNTOS_H_INCLUDED
