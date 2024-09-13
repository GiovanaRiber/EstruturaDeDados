#include "estoque.h" //interface
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct medicameto {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct arvore {
    Medicamento* m;
    Arvore* esquerda;
    Arvore* direita;
};

Arvore* CriaArvore (void) { return NULL; }

Medicamento* CriaMedicamento(int codigo, char* nome, float valor, int* data) {

    Medicamento* novo = (Medicamento*) malloc(sizeof(Medicamento));

    if (novo == NULL) { printf("Erro ao alocar memoria !\n"); exit(1); }

    strcpy(novo->nome, nome);
    novo->codigo = codigo;
    novo->valor = valor;

    for (int i = 0; i < 3; i++)
        novo->data[i] = data[i];

    return novo;
}

Arvore* InsereArvoreMedicamento(FILE * fp, Arvore* a, Medicamento* m){

    if (a == NULL) {

        Arvore* novo = (Arvore*) malloc(sizeof(Arvore));

        if (novo == NULL) { printf("Erro ao alocar memoria !\n"); exit(1); }

        novo->m = m;
        novo->esquerda = NULL;
        novo->direita = NULL;

        fprintf(fp, "MEDICAMENTO %s %d ADICIONADO\n", m->nome, m->codigo); // escreve a mensagem no arquivo

        return novo;
    }

    if (m->codigo < a->m->codigo)
        a->esquerda = InsereArvoreMedicamento(fp, a->esquerda, m); // se for maior, vai para a subárvore direita
    else
        a->direita = InsereArvoreMedicamento(fp, a->direita, m);// senão, vai para  a subárvore esquerda
    return a;
}

Arvore* RetiraArvoreMedicamento(FILE * fp, Arvore* a, int id_medicamento) {

    if (a == NULL) return NULL; // caso o medicamento não seja encontrado

    if (a->m->codigo == id_medicamento) {
        if (a->esquerda == NULL && a->direita == NULL) { // remover nó folha (sem filhos)
            fprintf(fp, "MEDICAMENTO %s %d RETIRADO\n", a->m->nome, a->m->codigo);
            free(a->m);
            free(a);
            return NULL;
        }

        if (a->esquerda != NULL && a->direita != NULL) { // remover nó com dois filhos
            Arvore* aux = a->direita;
            while (aux->esquerda != NULL)
                aux = aux->esquerda;

            // trocar o medicamento
            Medicamento* temp = a->m;
            a->m = aux->m;
            aux->m = temp;

            a->direita = RetiraArvoreMedicamento(fp, a->direita, id_medicamento); // remover o sucessor (que agora tem o código a ser removido)
            return a;
        } else { // remover nó com apenas um filho
            Arvore* aux;

            if (a->esquerda != NULL)
                aux = a->esquerda;
            else
                aux = a->direita;

            fprintf(fp, "MEDICAMENTO %s %d RETIRADO\n", a->m->nome, a->m->codigo);
            free(a->m);
            free(a);
            return aux;
        }

    } else { // continuar a busca na subárvore esquerda ou direita
        if (id_medicamento < a->m->codigo)
            a->esquerda = RetiraArvoreMedicamento(fp, a->esquerda, id_medicamento);
        else
            a->direita = RetiraArvoreMedicamento(fp, a->direita, id_medicamento);
        return a;
    }
}

void ImprimeArvoreMedicamentos(FILE *fp, Arvore* a) {

    if (a != NULL) {
        fprintf(fp, "MEDICAMENTO %s %d %.2f %d %d %d\n", a->m->nome, a->m->codigo, a->m->valor,
                a->m->data[0], a->m->data[1], a->m->data[2]);
        ImprimeArvoreMedicamentos(fp, a->esquerda);  // imprime subárvore esquerda
        ImprimeArvoreMedicamentos(fp, a->direita);   // imprime subárvore direita
    }
}

Arvore* AtualizaPreco(FILE * fp, Arvore* a, int codigo, float valor){

    if (a != NULL) {
        if (a->m->codigo == codigo) {
            a->m->valor = valor;
            fprintf(fp, "PRECO ATUALIZADO %s %d %.2f\n", a->m->nome, a->m->codigo, a->m->valor);
        }
        AtualizaPreco(fp, a->esquerda, codigo, valor); // percorre as subárvores
        AtualizaPreco(fp, a->direita, codigo, valor);
    }
    return a;
}

int AuxiliarValidade(FILE *fp, Arvore* a, int* data) {

    int cont = 0;

    if (a != NULL) {
        if (a->m->data[2] < data[2] ||
            (a->m->data[2] == data[2] && a->m->data[1] < data[1]) ||
            (a->m->data[2] == data[2] && a->m->data[1] == data[1] && a->m->data[0] < data[0])) {
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", a->m->nome, a->m->codigo);
            cont = 1;  // medicamento vencido encontrado
        }

        // verifica se há medicamentos vencidos nas subárvores
        if (AuxiliarValidade(fp, a->esquerda, data) ||
           (AuxiliarValidade(fp, a->direita, data)))
            cont = 1;  // subárvore esquerda encontrou medicamento vencido
    }
    return cont;
}

Arvore* VerificaArvoreValidade(FILE *fp, Arvore* a, int* data) {

    int cont = AuxiliarValidade(fp, a, data);

    if (cont == 0)
        fprintf(fp, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA ARVORE\n");

    return a;
}

int VerificaArvoreMedicamento(FILE *fp, Arvore* a, int id_medicamento) {

    if (a == NULL) { return 0; } // se a subárvore é vazia, medicamento não encontrado

    if (a->m->codigo == id_medicamento) { // medicamento encontrado
        fprintf(fp, "MEDICAMENTO %s %d ENCONTRADO\n", a->m->nome, a->m->codigo);
        return 1;
    }

    if (id_medicamento < a->m->codigo) // continua a busca na subárvore esquerda ou direita
        return VerificaArvoreMedicamento(fp, a->esquerda, id_medicamento);
    else
        return VerificaArvoreMedicamento(fp, a->direita, id_medicamento);
}

void LiberaArvore(Arvore* a) {

    if (a != NULL) {
        LiberaArvore(a->esquerda);
        LiberaArvore(a->direita);
        free(a->m);
        free(a);
    }
}