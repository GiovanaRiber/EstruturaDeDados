#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

typedef struct chapa Chapa;
typedef struct lista Lista;
typedef struct votacao TiposVotos;

Chapa* criarChapa (char *nome, int numero, int *data, char *nomeVice);

Lista* inserirChapaLista (Lista* lista, Chapa* c);

void visualizarChapas (Lista* lista);

void contarVotos (Lista* lista, int eleitores, TiposVotos *v);

void gerarBoletim (Lista* lista, TiposVotos v, FILE* arq, int eleitores);

void votacaoChapa (Lista* lista, int eleitores, int turno, FILE* arq, int tamLista);

void liberarLista (Lista* lista);

int compararIdade (int nasc1[3], int nasc2[3]);

int verificacaoNumero (Lista* lista, int numero);

void imprimirMaisVelho (Chapa* candidato1, Chapa* candidato2, const char* mensagem1, const char* mensagem2);

#endif // INTERFACE_H_INCLUDED