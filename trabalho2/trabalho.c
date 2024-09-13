#include "estoque.h" //interface
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    FILE * arq = fopen ("entrada.txt", "r");
    FILE * arq_saida = fopen ("saida.txt", "w");

    if (arq == NULL || arq_saida == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char aux_str[500]; // vetor auxiliar para leitura de comandos
    char nome[30];     // variáveis auxiliares
    int codigo;
    float valor;
    int data[3];

    Arvore *arvore = CriaArvore(); // Cria a árvore inicial
    Medicamento *m; // variável temporária para armazenar medicamentos

    while (fscanf(arq, "%s", aux_str) != EOF) {

        if (strcmp(aux_str, "MEDICAMENTO") == 0) {  // lê os dados do medicamento
            fscanf(arq, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);
            m = CriaMedicamento(codigo, nome, valor, data);
            arvore = InsereArvoreMedicamento(arq_saida, arvore, m); // insere o medicamento na árvore
        }
        else if (strcmp(aux_str, "RETIRA") == 0) {
            fscanf(arq, "%d", &codigo);
            arvore = RetiraArvoreMedicamento(arq_saida, arvore, codigo); // remove o medicamento pelo código
        }
        else if (strcmp(aux_str, "IMPRIME_ARVORE") == 0) {
            ImprimeArvoreMedicamentos(arq_saida, arvore); // imprime a árvore completa no arquivo
        }
        else if (strcmp(aux_str, "ATUALIZA_PRECO") == 0) {
            fscanf(arq, "%d %f", &codigo, &valor);
            arvore = AtualizaPreco(arq_saida, arvore, codigo, valor); // atualiza o preço do medicamento
        }
        else if (strcmp(aux_str, "VERIFICA_VALIDADE") == 0) {
            fscanf(arq, "%d %d %d", &data[0], &data[1], &data[2]);
            arvore =VerificaArvoreValidade(arq_saida, arvore, data); // verifica os medicamentos vencidos
        }
        else if (strcmp(aux_str, "VERIFICA_ARVORE") == 0) {
            fscanf(arq, "%d", &codigo);
            if (VerificaArvoreMedicamento(arq_saida, arvore, codigo)== 0){ // verifica se um medicamento existe na árvore
                fprintf(arq_saida, "MEDICAMENTO %d NAO ENCONTRADO NA ARVORE\n", codigo);
            }
        }
        else if(strcmp(aux_str, "FIM") == 0) {
            break; // FIM
        }
    }
    LiberaArvore(arvore); // libera a árvore
    fclose(arq_saida); // fecha os arquivos
    fclose(arq);

    return 0;
}