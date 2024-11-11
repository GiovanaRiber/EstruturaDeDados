#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct noArv {
    char info;
    struct noArv* esq;
    struct noArv* dir;
}; typedef struct noArv NoArv;

NoArv* arv_criavazia (void){return NULL;}

NoArv* arv_cria (char c, NoArv* sae, NoArv* sad){ // função criar

    NoArv* p=(NoArv*)malloc(sizeof(NoArv));

    if(p==NULL) exit(1);
        p->info = c;
        p->esq = sae;
        p->dir = sad;
    return p;
}

NoArv* arv_libera(NoArv* a){

    if (!arv_vazia(a)){
        arv_libera(a->esq); // libera sae
        arv_libera(a->dir); // libera sad 
        free(a);            // libera raiz
    }
    return NULL;
}

int arv_vazia(NoArv* a) { return a==NULL; }

int arv_pertence(NoArv* a, char c) {

    if (arv_vazia(a))
        return 0; // árvore vazia: não encontrou
    else
        return a->info==c ||
    arv_pertence(a->esq,c) ||
    arv_pertence(a->dir,c);
}

void arv_imprime (NoArv* a) { // Imprime

    if (!arv_vazia(a)){
        printf("%c ",a->info); // mostra raiz
        arv_imprime(a->esq); // mostra sae
        arv_imprime(a->dir); // mostra sad
    }
}

int main(){

    NoArv* a1 = arv_cria('d',arv_criavazia(),arv_criavazia());
    NoArv* a2= arv_cria('b',arv_criavazia(),a1);

    arv_imprime (a1);
    printf("\n");
    arv_imprime(a2);

    return 0;
}