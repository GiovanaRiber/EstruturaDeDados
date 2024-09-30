#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

struct chapa {
    char nome[50];
    int numero;
    int nascimento[3];
    char nomeVice[50];
    int votos;
    float porcentagem;
};

struct lista {
    Chapa *c;
    Lista *prox;
};

struct votacao {
    int nulos;
    int brancos;
    int votosTotais;
};

Chapa* criarChapa(char *nome, int numero, int *nascimento, char *nomeVice) {

    Chapa* nova = (Chapa*) malloc(sizeof(Chapa));
    if (nova == NULL){ printf("Erro ao alocar memoria !\n"); exit(1); }
    strcpy(nova->nome, nome);
    nova->numero = numero;
    for (int i = 0; i < 3; i++) nova->nascimento[i] = nascimento[i];
    strcpy(nova->nomeVice, nomeVice);

    return nova;
}

Lista* inserirChapaLista(Lista* lista, Chapa* c) {
    Lista* nova = (Lista*) malloc(sizeof(Lista));
    if (nova == NULL) { printf("Erro ao alocar memoria!\n"); exit(1); }
    nova->c = c;
    nova->prox = lista;
    return nova;
}

void visualizarChapas(Lista* lista) {
    while (lista != NULL) {
        printf("-----------------------------------\n");
        printf("| %-10s: %-19s |\n", "Candidato", lista->c->nome);
        printf("| %-10s: %-19s |\n", "Vice", lista->c->nomeVice);
        printf("| %-10s: %-19d |\n", "Numero", lista->c->numero);
        printf("-----------------------------------\n");
        lista = lista->prox;
    }
    printf("===================================\n");
}

int compararIdade(int nasc1[3], int nasc2[3]) {
    if (nasc1[2] != nasc2[2])
        return nasc1[2] - nasc2[2];
    else if (nasc1[1] != nasc2[1])
        return nasc1[1] - nasc2[1];
    else
        return nasc1[0] - nasc2[0];
}

int verificacaoNumero(Lista* lista, int numero) {
    Lista* temp = lista;
    while (temp != NULL) {
        if (temp->c->numero == numero) return 1;
        temp = temp->prox;
    }
    return 0;
}

void contarVotos(Lista* lista, int eleitores, TiposVotos *v) {

    int cont = 0, op = 0, quantEleitores = 0;

    while (cont < eleitores) {

        printf("\n============= VOTACAO =============\n");
        visualizarChapas(lista);

        printf("\nEleitor %d escolha seu candidato: ", quantEleitores + 1);
        scanf("%d", &op);

        system("cls");

        if (op == 0) {
            v->brancos++;
            v->votosTotais++;
            printf("\nVoto em branco confirmado !\n");
        } else {
            Lista* temp = lista;
            int achou = 0;

            while (temp != NULL) {
                if (temp->c->numero == op) {
                    temp->c->votos++;
                    v->votosTotais++;
                    printf("\nSeu voto em %s com Vice %s foi confirmado !\n", temp->c->nome, temp->c->nomeVice);
                    achou = 1;
                    break;
                }
                temp = temp->prox;
            }
            if (achou == 0) {
                v->nulos++;
                v->votosTotais++;
                printf("\nVoto nulo confirmado !\n");
            }
        }
        cont++;
        quantEleitores++;
    }
}

void gerarBoletim(Lista* lista, TiposVotos v, FILE* arq) {

    fprintf(arq, "================= BOLETIM ELEITORAL ================\n");
    fprintf(arq, "| %-20s | %-10s | %-10s |\n", "CANDIDATO", "VOTOS", "PORCENTAGEM");
    fprintf(arq, "----------------------------------------------------\n");

    Lista* temp = lista;
    int validos = 0;

    while (temp != NULL) {
        temp->c->porcentagem = (v.votosTotais > 0) ? ((float)temp->c->votos * 100 / v.votosTotais) : 0.0;
        fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", temp->c->nome, temp->c->votos, temp->c->porcentagem);
        validos += temp->c->votos;
        temp = temp->prox;
    }
    fprintf(arq, "----------------------------------------------------\n");
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS VALIDOS", validos,
            (v.votosTotais > 0) ? ((float)validos * 100 / v.votosTotais) : 0.0);
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS EM BRANCO", v.brancos,
            (v.votosTotais > 0) ? ((float)v.brancos * 100 / v.votosTotais) : 0.0);
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS NULOS", v.nulos,
            (v.votosTotais > 0) ? ((float)v.nulos * 100 / v.votosTotais) : 0.0);
    fprintf(arq, "----------------------------------------------------\n");
    fprintf(arq, "| %-20s | %-10d |\n", "TOTAL DE VOTOS", v.votosTotais);
    fprintf(arq, "====================================================\n");
}

void imprimirMaisVelho(Chapa* candidato1, Chapa* candidato2, const char* mensagem1, const char* mensagem2) {
    if (compararIdade(candidato1->nascimento, candidato2->nascimento) < 0)
        printf("%sO candidato %s com o Vice %s venceu a eleicao %s com %.2f%% dos votos !\n",
                mensagem1, candidato1->nome, candidato1->nomeVice, mensagem2, candidato1->porcentagem);
    else
        printf("%sO candidato %s com o Vice %s venceu a eleicao %s com %.2f%% dos votos !\n",
                mensagem1, candidato2->nome, candidato2->nomeVice, mensagem2, candidato2->porcentagem);
}

void votacaoChapa(Lista* lista, int eleitores, int turno, FILE* arq, int tamLista) {

    TiposVotos v = {0, 0, 0};
    Lista* temp = lista;

    while (temp != NULL) { temp->c->votos = 0; temp = temp->prox; }

    temp = lista;

    printf("\n==== INICIO DO %s TURNO =====\n", (turno == 1) ? "PRIMEIRO" : "SEGUNDO");

    contarVotos(lista, eleitores, &v);
    gerarBoletim(lista, v, arq);

    Lista* candidato1 = NULL, *candidato2 = NULL;

    while (temp != NULL) {

        if (candidato1 == NULL || temp->c->votos > candidato1->c->votos) {
            candidato2 = candidato1;
            candidato1 = temp;
        } else if (candidato2 == NULL || temp->c->votos > candidato2->c->votos)
            candidato2 = temp;

        if (turno == 1 && temp->c->porcentagem > 50.00) {
            system("cls");
            printf("O candidato %s venceu a eleicao no primeiro turno com %.2f%% dos votos !\n",
                   temp->c->nome, temp->c->porcentagem);
            return;
        }
        temp = temp->prox;
    }

    if (turno == 1) {
        if (eleitores >= 10 && tamLista != 2) {

            printf("Nenhum candidato obteve mais de 50%% dos votos validos. Havera segundo turno !\n");
            fprintf(arq, "HAVERA SEGUNDO TURNO!");

            Lista* listaTemp = NULL;
            listaTemp = inserirChapaLista(listaTemp, candidato2->c);
            listaTemp = inserirChapaLista(listaTemp, candidato1->c);

            FILE* arq2 = fopen("turno_2.txt", "w");
            if (arq2 == NULL) { printf("Erro ao abrir o arquivo !\n"); exit(1); }

            votacaoChapa(listaTemp, eleitores, 2, arq2, tamLista);
            fclose(arq2);
            liberarLista(listaTemp);
            return;

        } else if (eleitores < 10) {
            imprimirMaisVelho(candidato1->c, candidato2->c,
            "Nao ha eleitores suficientes para um segundo turno, logo, o candidato mais velho vencera!\n", "no primeiro turno");
            return;

        } else if (tamLista == 2) {
            imprimirMaisVelho(candidato1->c, candidato2->c,
            "Nenhum dos dois candidatos obteve mais de 50%% dos votos, logo, o candidato mais velho vencera!\n", "no primeiro turno");
            return;
        }
     } else {

        if (candidato1->c->votos > candidato2->c->votos)
            printf("O candidato %s com o vice %s venceu a eleicao no segundo turno com %.2f%% dos votos!\n",
                    candidato1->c->nome, candidato1->c->nomeVice, candidato1->c->porcentagem);
        else if (candidato1->c->votos < candidato2->c->votos)
            printf("O candidato %s com o vice %s venceu a eleicao no segundo turno com %.2f%% dos votos!\n",
                    candidato2->c->nome, candidato2->c->nomeVice, candidato2->c->porcentagem);
        else
            imprimirMaisVelho(candidato1->c, candidato2->c, "Empate! O candidato mais velho vencera!\n", "no segundo turno");
    }
}

void liberarLista(Lista* lista) {
    while (lista != NULL) {
        Lista* temp = lista;
        lista = lista->prox;
        free(temp->c);
        free(temp);
    }
}