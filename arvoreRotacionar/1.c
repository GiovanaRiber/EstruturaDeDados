#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int altura;
} Arvore;

Arvore* raiz = NULL;

int altura(Arvore* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

int maior(int a, int b) {
    return (a >= b) ? a : b;
}

int obterBalanceamento(Arvore* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

Arvore* criarNo(int valor) {
    Arvore* no = malloc(sizeof(Arvore));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

Arvore* rotacionarDireita(Arvore* no) {
    Arvore* novoPai = no->esquerda;
    Arvore* temp = novoPai->direita;
    novoPai->direita = no;
    no->esquerda = temp;
    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    novoPai->altura = 1 + maior(altura(novoPai->esquerda), altura(novoPai->direita));
    return novoPai;
}

Arvore* rotacionarEsquerda(Arvore* no) {
    Arvore* novoPai = no->direita;
    Arvore* temp = novoPai->esquerda;
    novoPai->esquerda = no;
    no->direita = temp;
    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    novoPai->altura = 1 + maior(altura(novoPai->esquerda), altura(novoPai->direita));
    return novoPai;
}

Arvore* inserirElemento(Arvore* arvore, int valor) {
    if (arvore == NULL)
        return criarNo(valor);
    if (valor < arvore->valor)
        arvore->esquerda = inserirElemento(arvore->esquerda, valor);
    else if (valor > arvore->valor)
        arvore->direita = inserirElemento(arvore->direita, valor);
    else
        return arvore;

    arvore->altura = 1 + maior(altura(arvore->esquerda), altura(arvore->direita));
    int balanceamento = obterBalanceamento(arvore);

    if (balanceamento < -1) { // caso de rotação à direita
        if (valor < arvore->direita->valor) {
            arvore->direita = rotacionarDireita(arvore->direita);
        }
        arvore = rotacionarEsquerda(arvore);
    }

    if (balanceamento > 1) { // caso de rotação à esquerda
        if (valor > arvore->esquerda->valor) {
            arvore->esquerda = rotacionarEsquerda(arvore->esquerda);
        }
        arvore = rotacionarDireita(arvore);
    }

    return arvore;
}

void exibirEmOrdem(Arvore* arvore) {
    if (arvore != NULL) {
        exibirEmOrdem(arvore->esquerda);
        printf("%d ", arvore->valor);
        exibirEmOrdem(arvore->direita);
    }
}

int main() {
    
    raiz = inserirElemento(raiz, 50);
    exibirEmOrdem(raiz);
    printf("\n");
    
    raiz = inserirElemento(raiz, 30);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 70);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 40);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 10);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 60);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 80);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 5);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 4);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 3);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 2);
    exibirEmOrdem(raiz);
    printf("\n");

    raiz = inserirElemento(raiz, 1);
    exibirEmOrdem(raiz);
    printf("\n");

    return 0;
}
