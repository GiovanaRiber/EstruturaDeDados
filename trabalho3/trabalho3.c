#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

int main() {

    Lista* lista = NULL;
    Chapa* c;

    FILE *arq1 = fopen("turno_1.txt", "w");
    if (arq1 == NULL) { printf("Erro ao abrir o arquivo!\n"); exit(1); }

    int eleitores, num;

    printf("Insira o numero e eleitores: ");
    scanf("%d", &eleitores);

    while(eleitores < 0) {
        printf("Valores negativos nao sao validos: ");
        scanf("%d", &eleitores);
     }

    printf("Insira o numero de chapas a serem cadastradas: ");
    scanf("%d", &num);

     while (num < 0 || num  > 99) {
        printf("Valor invalido! Tente novamente: ");
        scanf("%d", &num);
     }

    char nome[50], nomeVice[50];
    int numero, nascimento[3];
    int op = 0, cont = 0, quantCandidatos = 0;

    while (op != 2 && cont < num) {

        printf("\n ======================================");
        printf("\n|Opcao [1] = Cadastrar chapa !         |");
        printf("\n|Opcao [2] = Sair !                    |");
        printf("\n ======================================\n");

        if (op != 2) {

            scanf("%d", &op);

            switch (op) {
                case 1:
                    system("cls");
                    setbuf(stdin, NULL);
                    printf("\n======== Cadastrar Candidado %d ========\n", quantCandidatos + 1);
                    printf("\nInsira o nome do canditado: ");
                    fgets(nome, 50, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    printf("Insira o nome do vice: ");
                    fgets(nomeVice, 50, stdin);
                    nomeVice[strcspn(nomeVice, "\n")] = '\0';

                    printf("Insira o numero do candidato: ");
                    scanf("%d", &numero);

                    while (numero < 0 || numero > 99 || verificacaoNumero(lista, numero)) {
                        if (numero < 0 || numero > 99)
                            printf("Numero invalido! Tente novamente: ");
                        else
                            printf("Este numero ja foi utilizado! Escolha outro: ");

                        scanf("%d", &numero);
                    }

                    printf("Insira a data de nascimento do candidato [dd mm aaaa]: ");
                    for (int i = 0; i < 3; i++)
                        scanf("%d", &nascimento[i]);

                    c = criarChapa(nome, numero, nascimento, nomeVice);
                    lista = inserirChapaLista(lista, c);
                    quantCandidatos++;

                    cont++;
                    break;

                case 2:
                    break;

                default:
                    printf("Opcao invalida !");
            }
        }
    }

    system("cls");

    if (quantCandidatos > 1) {
        votacaoChapa(lista, eleitores, 1, arq1, quantCandidatos);
        liberarLista(lista);
    } else
        printf("\nImpossivel prosseguir! Fim do programa !");

    fclose(arq1);
    return 0;
}
