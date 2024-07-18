#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estoque.h"

int main(){

    FILE *arq = fopen("entrada.txt", "r");
    FILE *arq_saida = fopen("saida.txt", "w");

    Lista* lista = CriaLista();

    if(arq == NULL || arq_saida == NULL){
        printf("Erro ao abrir o arquivo!\n"); exit(1);
    }

    char aux_str[250]; //vetor auxiliar
    char nome[20]; //variáveis auxiliares
    int codigo;
    float valor;
    int data[3];

    while(fscanf(arq, "%s", aux_str) != EOF){ //arquivo de entrada é lido linha, a linha

        if(strcmp(aux_str, "MEDICAMENTO") == 0){ //compara se o vetor auxiliar é igual a string "MEDICAMENTO"

            fscanf(arq, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]); //as variáveis auxiliares recebem os dados scaneados da linha
            lista = InsereListaMedicamento(arq_saida, lista, codigo, nome, valor, data); //função de inserir é chamada
        }
        else if(strcmp(aux_str, "RETIRA") == 0){

            fscanf(arq, "%d", &codigo);
            lista = RetiraListaMedicamento(arq_saida, lista, codigo);
        }
        else if(strcmp(aux_str, "IMPRIME_LISTA") == 0){

            ImprimeListaMedicamentos(arq_saida, lista);
        }
        else if(strcmp(aux_str, "ATUALIZA_PRECO") == 0){

            fscanf(arq, "%d %f", &codigo, &valor);
            lista = AtulizaPreco(arq_saida, lista, codigo, valor);
        }
        else if(strcmp(aux_str, "VERIFICA_VALIDADE") == 0){

            fscanf(arq, "%d %d %d", &data[0], &data[1], &data[2]);
            VerificaListaValidade(arq_saida, lista, data);
        }
        else if(strcmp(aux_str, "VERIFICA_LISTA") == 0){

            fscanf(arq, "%d", &codigo);
            VerificaListaMedicamento(arq_saida, lista, codigo);

        }
        else if(strcmp(aux_str, "ORDENA_LISTA_VALIDADE") == 0){

            lista = OrdenaListaVencimento(lista);
        }
        else if(strcmp(aux_str, "IMPRIME_LISTA") == 0){

            ImprimeListaMedicamentos(arq_saida, lista);
        }
        else if(strcmp(aux_str, "VERIFICA_VALIDADE") == 0){

            fscanf(arq, "%d %d %d", &data[0], &data[1], &data[2]);
            VerificaListaValidade(arq_saida, lista, data);
        }
        else if(strcmp(aux_str, "ORDENA_LISTA_VALOR") == 0){

            lista = OrdenaListaValor(lista);
        }
        else if(strcmp(aux_str, "IMPRIME_LISTA") == 0){

            ImprimeListaMedicamentos(arq_saida, lista);
        }
        else if(strcmp(aux_str, "FIM") == 0){
            break;
        }
    }
    fclose(arq_saida); //fecha os arquivos
    fclose(arq);

    LiberaLista(lista);

    return 0;
}
