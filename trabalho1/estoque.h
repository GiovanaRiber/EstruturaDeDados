#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct medicamento{
    int codigo;
    char nome[20];
    float valor;
    int data[3];
}; typedef struct medicamento  Medicamento;

struct Lista{
    Medicamento *m;
    struct Lista *prox;
}; typedef struct Lista Lista;

Lista* CriaMedicamento (char * nome, int codigo, float valor, int *data);

Lista* CriaLista(void);

Lista* InsereListaMedicamento(FILE * fp, Lista* lista, int codigo, char *nome, float valor, int *data);

Lista* RetiraListaMedicamento(FILE * fp , Lista* lista , int codigo);

void ImprimeListaMedicamentos(FILE * fp , Lista* lista);

Lista* AtulizaPreco(FILE * fp, Lista* lista, int codigo, float valor);

void VerificaListaValidade(FILE * fp, Lista* lista, int *data);

void VerificaListaMedicamento(FILE * fp , Lista* lista , int codigo);

Lista* OrdenaListaVencimento (Lista* lista);

int ComparaDatas(int *data1, int *data2);

void Trocar(Lista* lst1, Lista* lst2);

Lista* OrdenaListaValor (Lista* lista);

void LiberaLista(Lista* lista);

#endif // ESTOQUE_H_INCLUDED
