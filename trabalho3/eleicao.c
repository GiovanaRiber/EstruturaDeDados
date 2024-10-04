#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleicao.h"

struct chapa { // para armazenar as chapas eleitorais
    char nome[50];
    int numero;
    int nascimento[3];
    char nomeVice[50];
    int votos;
    float porcentagem;
};

struct lista { // lista 
    Chapa *c;
    Lista *prox;
};

struct votacao { // para armazenar os tipos diferentes de votos
    int nulos;
    int brancos;
    int votosTotais;
};

Chapa* criarChapa(char *nome, int numero, int *nascimento, char *nomeVice) { // criação da chapa eleitoral

    Chapa* nova = (Chapa*) malloc(sizeof(Chapa));
    if (nova == NULL){ printf("Erro ao alocar memoria !\n"); exit(1); }
    strcpy(nova->nome, nome);
    nova->numero = numero;
    for (int i = 0; i < 3; i++) nova->nascimento[i] = nascimento[i];
    strcpy(nova->nomeVice, nomeVice); // faz uma cópia da variável

    return nova;
}

Lista* inserirChapaLista(Lista* lista, Chapa* c) {
    Lista* nova = (Lista*) malloc(sizeof(Lista));
    if (nova == NULL) { printf("Erro ao alocar memoria!\n"); exit(1); }
    nova->c = c;
    nova->prox = lista;
    return nova;
}

void visualizarChapas(Lista* lista) { // impressão das chapas
    while (lista != NULL) {
        printf("-----------------------------------\n");
        printf("| %-10s: %-19s |\n", "Candidato", lista->c->nome); // formatação de espaço
        printf("| %-10s: %-19s |\n", "Vice", lista->c->nomeVice);
        printf("| %-10s: %-19d |\n", "Numero", lista->c->numero);
        printf("-----------------------------------\n");
        lista = lista->prox;
    }
    printf("===================================\n");
}

int compararIdade(int nasc1[3], int nasc2[3]) { // comparar a idade dos candidadatos
    if (nasc1[2] != nasc2[2])
        return nasc1[2] - nasc2[2]; // para ano
    else if (nasc1[1] != nasc2[1])
        return nasc1[1] - nasc2[1]; // para mês
    else
        return nasc1[0] - nasc2[0]; // para dia
}

int verificacaoNumero(Lista* lista, int numero) { // confirmar se número cadastrado já ñ foi atrubuido a outro candidato
    Lista* temp = lista;
    while (temp != NULL) {
        if (temp->c->numero == numero) return 1;
        temp = temp->prox;
    }
    return 0;
}

void contarVotos(Lista* lista, int eleitores, TiposVotos *v) { // contar e armazenar os votos

    int cont = 0, op = 0, quantEleitores = 0; // variáveis auxiliares

    while (cont < eleitores) {

        printf("\n============= VOTACAO =============\n");
        visualizarChapas(lista);

        printf("\nEleitor %d escolha seu candidato: ", quantEleitores + 1); // formalidade para visualização da quantidade de eleitores
        scanf("%d", &op); // opção do eleitor

        system("cls"); // limpeza

        if (op == 0) { // se o eleitor votar em branco
            v->brancos++;
            v->votosTotais++;
            printf("\nVoto em branco confirmado !\n");
        } else {
            Lista* temp = lista;
            int achou = 0; // variável de controle

            while (temp != NULL) {
                if (temp->c->numero == op) { // se o número digitado for igual ao do candidato armazenado
                    temp->c->votos++;
                    v->votosTotais++;
                    printf("\nSeu voto em %s com Vice %s foi confirmado !\n", temp->c->nome, temp->c->nomeVice);
                    achou = 1; // incremento para indicar que o candidato foi encontrado na lista 
                    break;
                }
                temp = temp->prox;
            }
            if (achou == 0) { // caso o número digitado ñ seja igual ao de nenhum candidato cadastrado
                v->nulos++;
                v->votosTotais++;
                printf("\nVoto nulo confirmado !\n");
            }
        }
        cont++; // incremento para a continuação do loop
        quantEleitores++; // incremento de eleitores
    }
}

void gerarBoletim(Lista* lista, TiposVotos v, FILE* arq) {

    fprintf(arq, "================= BOLETIM ELEITORAL ================\n");
    fprintf(arq, "| %-20s | %-10s | %-10s |\n", "CANDIDATO", "VOTOS", "PORCENTAGEM"); // formatar a distância das mensagens no arquivo
    fprintf(arq, "----------------------------------------------------\n");

    Lista* temp = lista;
    int validos = 0; // referente aos votos válidos, ou seja, ñ nulos e ñ brancos 

    while (temp != NULL) {
        temp->c->porcentagem = (v.votosTotais > 0) ? ((float)temp->c->votos * 100 / v.votosTotais) : 0.0; // cálculo simplificado da porcentagem
        fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", temp->c->nome, temp->c->votos, temp->c->porcentagem); // |  
        validos += temp->c->votos; // incrementa os votos válidos                                                -> adiciona 0.0 se necessário para evitar a divisão por zero
        temp = temp->prox;
    }
    fprintf(arq, "----------------------------------------------------\n");
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS VALIDOS", validos,
            (v.votosTotais > 0) ? ((float)validos * 100 / v.votosTotais) : 0.0); // porcentagem dos válidos
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS EM BRANCO", v.brancos,
            (v.votosTotais > 0) ? ((float)v.brancos * 100 / v.votosTotais) : 0.0); // porcentagem dos brancos
    fprintf(arq, "| %-20s | %-10d | %10.2f%% |\n", "VOTOS NULOS", v.nulos,
            (v.votosTotais > 0) ? ((float)v.nulos * 100 / v.votosTotais) : 0.0); // porcentagem dos nulos
    fprintf(arq, "----------------------------------------------------\n");
    fprintf(arq, "| %-20s | %-10d |\n", "TOTAL DE VOTOS", v.votosTotais);
    fprintf(arq, "====================================================\n");
}

void imprimirMaisVelho(Chapa* candidato1, Chapa* candidato2, const char* mensagem1, const char* mensagem2) { // imprimir mensagem de vitória em relação a idade dos candidatos
    if (compararIdade(candidato1->nascimento, candidato2->nascimento) < 0) // caso o primeito candidato seja mais velho
        printf("%sO candidato %s com o Vice %s venceu a eleicao %s com %.2f%% dos votos !\n",
                mensagem1, candidato1->nome, candidato1->nomeVice, mensagem2, candidato1->porcentagem);
    else
        printf("%sO candidato %s com o Vice %s venceu a eleicao %s com %.2f%% dos votos !\n", // caso o segundo candidato seja mais velho
                mensagem1, candidato2->nome, candidato2->nomeVice, mensagem2, candidato2->porcentagem);
}

void votacaoChapa(Lista* lista, int eleitores, int turno, FILE* arq, int tamLista) {

    TiposVotos v = {0, 0, 0}; // zera os votos da struct TiposVotos
    Lista* temp = lista;

    while (temp != NULL) { temp->c->votos = 0; temp = temp->prox; } // zera os votos de cada candidato em seu respectivo nó

    temp = lista; // inicialida a variável novamente

    printf("\n==== INICIO DO %s TURNO =====\n", (turno == 1) ? "PRIMEIRO" : "SEGUNDO"); // comparação simplificada para impressão da mensagem

    contarVotos(lista, eleitores, &v); // chama função de contagem
    gerarBoletim(lista, v, arq); // gera o boletim eleitoral

    Lista* candidato1 = NULL, *candidato2 = NULL; // variáveis do tipo Lista
 
    while (temp != NULL) {

        if (candidato1 == NULL || temp->c->votos > candidato1->c->votos) { // comparação para armazenar os dois cadidatos mais votados
            candidato2 = candidato1;
            candidato1 = temp; // atualização
        } else if (candidato2 == NULL || temp->c->votos > candidato2->c->votos)
            candidato2 = temp; // atualização

        if (turno == 1 && temp->c->porcentagem > 50.00) { // verifica a porcentagem para declarar a possível vitória
            system("cls");
            printf("O candidato %s venceu a eleicao no primeiro turno com %.2f%% dos votos !\n",
                   temp->c->nome, temp->c->porcentagem);
            return;
        }
        temp = temp->prox;
    }

    if (turno == 1) { // caso ñ tenha vencendor com base nas porcentagem

        if (tamLista == 2) {

            if (candidato1->c->votos == candidato2->c->votos) { // caso tenha empate entre os candidatos
                imprimirMaisVelho(candidato1->c, candidato2->c,
                "Empate! O candidato mais velho vencera!\n", "no primeiro turno");
                return;
            }

            // caso haja apenas dois candidatos na lista, ñ vai pra segundo turno, logo, o candidato mais velho vencerá
            imprimirMaisVelho(candidato1->c, candidato2->c,
            "Nenhum dos dois candidatos obteve mais de 50%% dos votos, logo, o candidato mais velho vencera!\n", "no primeiro turno");
            return;
        }

        if (eleitores >= 10 && tamLista != 2) { // caso tenha mais de 10 eleitores e mais de dois candidatos, vai para o segundo turno

            printf("Nenhum candidato obteve mais de 50%% dos votos validos. Havera segundo turno !\n");
            fprintf(arq, "HAVERA SEGUNDO TURNO!");

            Lista* listaTemp = NULL; // lista auxiliar para armazenar os dois candidatos mais votados para ir ao segundo turno 
            listaTemp = inserirChapaLista(listaTemp, candidato2->c); // adição candidato 1
            listaTemp = inserirChapaLista(listaTemp, candidato1->c); // adição candidato 2

            FILE* arq2 = fopen("turno_2.txt", "w"); // abertura do arquivo referente ao segundo turno
            if (arq2 == NULL) { printf("Erro ao abrir o arquivo !\n"); exit(1); }

            votacaoChapa(listaTemp, eleitores, 2, arq2, tamLista); // chamada recursiva para o segundo turno
            fclose(arq2); // fechamento do arquivo
            liberarLista(listaTemp); // liberação da memória da lista auxiliar 
            return;

        } else if (eleitores < 10) { // caso tenha menos de 10 eleitores ñ vai para segundo turno e o candidato mais velho ganha
            imprimirMaisVelho(candidato1->c, candidato2->c,
            "Nao ha eleitores suficientes para um segundo turno, logo, o candidato mais velho vencera!\n", "no primeiro turno");
            return;

        } 
     } else { // caso sera o segundo turno

        if (candidato1->c->votos > candidato2->c->votos) // primeiro candidato vence
            printf("O candidato %s com o vice %s venceu a eleicao no segundo turno com %.2f%% dos votos!\n",
                    candidato1->c->nome, candidato1->c->nomeVice, candidato1->c->porcentagem);
        else if (candidato1->c->votos < candidato2->c->votos) // segundo candidato vence
            printf("O candidato %s com o vice %s venceu a eleicao no segundo turno com %.2f%% dos votos!\n",
                    candidato2->c->nome, candidato2->c->nomeVice, candidato2->c->porcentagem);
        else // empate
            imprimirMaisVelho(candidato1->c, candidato2->c, "Empate! O candidato mais velho vencera!\n", "no segundo turno");
    }
}

void liberarLista(Lista* lista) { // liberação de memória 
    while (lista != NULL) {
        Lista* temp = lista;
        lista = lista->prox;
        free(temp->c);
        free(temp);
    }
}