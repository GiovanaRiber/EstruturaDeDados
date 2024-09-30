#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct medicameto Medicamento;
typedef struct arvore Arvore;
typedef struct votacao TiposVotos;

Medicamento* CriaMedicamento (int codigo, char* nome, float valor, int* data);

Arvore* CriaArvore();

Arvore* InsereArvoreMedicamento (FILE * fp, Arvore* a, Medicamento* m);

Arvore* RetiraArvoreMedicamento (FILE * fp, Arvore* a, int id_medicamento);

int VerificaArvoreMedicamento(FILE * fp, Arvore* a, int id_medicamento);

Arvore* VerificaArvoreValidade (FILE * fp, Arvore* a, int* data);

int AuxiliarValidade(FILE * fp, Arvore* a, int* data);

Arvore* AtualizaPreco (FILE * fp, Arvore* a, int codigo, float valor);

void ImprimeArvoreMedicamentos (FILE * fp, Arvore* a);

void LiberaArvore (Arvore* a);

#endif // ESTOQUE_H_INCLUDED
