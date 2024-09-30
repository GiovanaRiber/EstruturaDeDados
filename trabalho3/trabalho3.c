#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

int main() {

    Lista* lista = NULL; // criação da lista
    Chapa* c;

    FILE *arq1 = fopen("turno_1.txt", "w"); // abertura do arquivo para o segundo turno
    if (arq1 == NULL) { printf("Erro ao abrir o arquivo!\n"); exit(1); }

    int eleitores, num;

    printf("Insira o numero e eleitores: ");
    scanf("%d", &eleitores);

    while(eleitores < 0 || eleitores < 2) { // verificação adicional
        printf("Valor invalido! Tente novamente: ");
        scanf("%d", &eleitores);
     }

    printf("Insira o numero de chapas a serem cadastradas: ");
    scanf("%d", &num);

     while (num < 0 || num  > 99) { // verificação adicional
        printf("Valor invalido! Tente novamente: ");
        scanf("%d", &num);
     }

    char nome[50], nomeVice[50];
    int numero, nascimento[3];
    int op = 0, cont = 0, quantCandidatos = 0;

    while (op != 2 && cont < num) { // loop referente as chapas eleitorais

        printf("\n ======================================"); // opções 
        printf("\n|Opcao [1] = Cadastrar chapa !         |");
        printf("\n|Opcao [2] = Sair !                    |"); // o usuário pode sair antes de cadastrar todas as chapas
        printf("\n ======================================\n");

        if (op != 2) { 

            scanf("%d", &op); // opção lida

            switch (op) {
                case 1:
                    system("cls");
                    setbuf(stdin, NULL);
                    printf("\n======== Cadastrar Candidado %d ========\n", quantCandidatos + 1);
                    printf("\nInsira o nome do canditado: ");
                    fgets(nome, 50, stdin);
                    nome[strcspn(nome, "\n")] = '\0'; // tira espaços vazios da string

                    printf("Insira o nome do vice: ");
                    fgets(nomeVice, 50, stdin);
                    nomeVice[strcspn(nomeVice, "\n")] = '\0'; // tira espaços vazios da string

                    printf("Insira o numero do candidato: ");
                    scanf("%d", &numero);

                    while (numero < 0 || numero > 99 || verificacaoNumero(lista, numero)) { // chamada para que ñ tenha candidatos com o mesmo número
                        if (numero < 0 || numero > 99)
                            printf("Numero invalido! Tente novamente: ");
                        else
                            printf("Este numero ja foi utilizado! Escolha outro: ");

                        scanf("%d", &numero);
                    }

                    printf("Insira a data de nascimento do candidato [dd mm aaaa]: ");
                    for (int i = 0; i < 3; i++)
                        scanf("%d", &nascimento[i]);

                    c = criarChapa(nome, numero, nascimento, nomeVice); // criação da chama eleitoral
                    lista = inserirChapaLista(lista, c); // inserção na lista
                    quantCandidatos++; // referente a quantidade de canditados, ou seja, o tamanho da lista

                    cont++;
                    break;

                case 2:
                    break;

                default:
                    printf("Opcao invalida !"); // para números que ñ estejam nas opções 
            }
        }
    }

    system("cls");

    if (quantCandidatos > 1) { // deve haver mais de um candidato para a votação se iniciar
        votacaoChapa(lista, eleitores, 1, arq1, quantCandidatos);
        liberarLista(lista);
    } else
        printf("\nImpossivel prosseguir! Fim do programa !");

    fclose(arq1); // fecha o arquivo do primeiro turno
    return 0;
}
