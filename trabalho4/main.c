#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"

int main() {

    Set* set1 = NULL;
    Set* set2 = NULL;

    add(&set1, 1);
    add(&set1, 3);
    add(&set1, 2);
    add(&set1, 4);
    add(&set1, 7);
    add(&set1, 20);

    add(&set2, 1);
    add(&set2, 3);
    add(&set2, 2);

    printf("Set 1: ");
    printSet(set1);
    printf("\n");

    printf("Set 2: ");
    printSet(set2);
    printf("\n");

    printf("\nSet 1 vazio: %s\n", isEmpty(set1) ? "true" : "false");
    printf("\nSet 2 vazio: %s\n", isEmpty(set2) ? "true" : "false");

    printf("\nTamanho conjunto 1: %d\n", len(set1));

    int aux = 20;

    printf("\n%d esta em conjunto 1? %s\n", aux, isIn(set1, aux) ? "true" : "false");

    printf("\nInterseccao vazia: %s \n", isDisjoint(set1, set2) ? "true" : "false");

    removeElem(&set1, aux);
    printf("\nElemento %d removido\n", aux);
    printf("Set 1: ");
    printSet(set1);
    printf("\n");

    Set* set3 = unionConj(set1, set2);

    printf("\nUniao Set 1 e Set 2: ");
    printSet(set3);
    printf("\n");

    Set* set4 = intersection(set1, set2);

    printf("\nInterseccao Set: ");
    printSet(set4);
    printf("\n");

    Set* set5 = difference(set1, set2);

    printf("\nDiferenca (Set 1 - Set 2): ");
    printSet(set5);
    printf("\n");

    printf("Set 1:");
    printSet(set1);
    printf("\n");

    printf("Set 2: ");
    printSet(set2);
    printf("\n");

    Set* set6 = symmetric_difference(set1, set2);

    printf("\nSymmetric Difference: ");
    printSet(set6);
    printf("\n");

    printf("\nSet 1 e subconjunto de Set 2: %s\n", isSubSet(set1, set2) ? "true" : "false");

    printf("\nSet 1 e superconjunto de Set 2: %s\n", isSuperSet(set1, set2) ? "true" : "false");

    copyConj(set1, &set2);

    printf("\nSet 2 apos a copia: ");
    printSet(set2);
    printf("\n");

    Elemento removido = pop(&set1);

    printf("\nElemento removido: %d\n", removido.info);
    printf("Set 1 apos remover: ");
    printSet(set1);

    clearConj(&set1);
    clearConj(&set2);
    clearConj(&set3);
    clearConj(&set4);
    clearConj(&set5);
    clearConj(&set6);

}
