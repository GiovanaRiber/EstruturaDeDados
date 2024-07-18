#include "estoque.h" //interface
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Lista* CriaLista(void){ return NULL; }

Lista* CriaMedicamento(char *nome, int codigo, float valor, int *data){

    Lista* novo = (Lista*) malloc(sizeof(Lista));

    if(novo == NULL){
        printf("Erro ao alocar memoria!\n"); exit(1);
    }

    novo->m = (Medicamento*) malloc(sizeof(Medicamento));

    if(novo == NULL){
        printf("Erro ao alocar memoria!\n"); exit(1);
    }

    strcpy(novo->m->nome, nome); //copia o nome recibido para o campo "Medicamento" do nó
    novo->m->codigo = codigo;
    novo->m->valor = valor;
    for(int i = 0; i < 3; i++) // preencher o vetor data
        novo->m->data[i] = data[i];

    novo->prox = NULL;

    return novo;
}

Lista* InsereListaMedicamento(FILE * fp, Lista* lista, int codigo, char *nome, float valor, int *data){

    Lista *novo = CriaMedicamento(nome, codigo, valor, data);
    novo->prox = lista; //adiciona o nó na lista

    fprintf(fp, "MEDICAMENTO %s %d ADICIONADO\n", nome, codigo);

    return novo;
}

Lista* RetiraListaMedicamento(FILE * fp, Lista* lista, int codigo){

    Lista* lst = lista;
    Lista* ant = NULL;

    while(lst != NULL && lst->m->codigo != codigo){ //loop para armazanar o nó anterior ao campo que possui o cógigo
        ant = lst;
        lst = lst->prox;
    }

    if(lst == NULL) //caso o código não tenha sido encontrado na lista
        return lista;

    fprintf(fp, "MEDICAMENTO %s %d RETIRADO\n", lst->m->nome, lst->m->codigo);

    if(ant == NULL) //caso o código tenha sido encontrado no primeiro nó
        lista = lst->prox;

    else
        ant->prox = lst->prox;

    free(lst->m); //liberação da memória
    free(lst);

    return lista;
}

void ImprimeListaMedicamentos(FILE * fp, Lista* lista){

    Lista* lst = lista;
    while(lst != NULL){ //loop para percorrer a lista até o final
        fprintf(fp, "%s %d %.2f %d %d %d\n", lst->m->nome, lst->m->codigo,
                lst->m->valor, lst->m->data[0], lst->m->data[1], lst->m->data[2]); //cada informação da lista é escrita no arquivo

        lst = lst->prox;
    }
}

Lista* AtulizaPreco(FILE * fp, Lista* lista, int codigo, float valor){

    Lista* lst = lista;

    while(lst != NULL){

        if(lst->m->codigo == codigo){ //condição para verificar se o código foi encontrado na lista

            lst->m->valor = valor; //atualização do valor para o que foi recebido por parâmetro

            fprintf(fp, "PRECO ATUALIZADO %s %d %.2f\n", lst->m->nome, lst->m->codigo, lst->m->valor);
            break;
        }
        lst = lst->prox;
    }
    return lista;
}

void VerificaListaValidade(FILE * fp, Lista* lista, int *data){

    Lista* lst = lista;
    int cont = 0;

    while(lst != NULL){

        if(lst->m->data[0] == data[0] && lst->m->data[1] == data[1] && lst->m->data[2] == data[2]){ //comparação da data da lista com a data forecida pela função

            if(lst->m->data[1] >= 6 && lst->m->data[2] <= 2024){ // condição para verificar a validade, considerando a data atual como 06/2024

                fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", lst->m->nome, lst->m->codigo);

                cont = 1; // indica se o medicamento foi encontrado
                break;
            }
        }
        lst = lst->prox;
    }
    if(!cont) // caso o medicamento não seja encontrado
        fprintf(fp, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA LISTA\n");

}

void VerificaListaMedicamento(FILE * fp, Lista* lista, int codigo){

    Lista* lst = lista;

    while(lst != NULL){

        if(lst->m->codigo == codigo){ //verifica se o código contido na lista é igual ao código fornecido

            fprintf(fp, "MEDICAMENTO ENCONTRADO NA LISTA\n");

            return; //sai do loop assim que escontra o medicamento
        }
        lst = lst->prox;
    }
    fprintf(fp, "MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
}

int ComparaDatas(int *data1, int *data2){ //retorna a diferença entre as datas

    if(data1[2] != data2[2]) //compara ano         se a diferença seja negativa, data1 é anterior à data2
        return data1[2] - data2[2];              //se a diferença seja positiva, data1 é posteror à que data2

    else if(data1[1] != data2[1])//compara mês
        return data1[1] - data2[1];

    else
        return data1[0] - data2[0];//compara dia

}

void Trocar(Lista* lst1, Lista* lst2){

    Medicamento* temp = lst1->m; //recebe o medicamento da lista 1

    lst1->m = lst2->m; //troca os medicamento de lugar
    lst2->m = temp;

}

Lista* OrdenaListaVencimento(Lista* lista){

    Lista* lst1 = lista;

    while(lst1 != NULL){

        Lista* lst2 = lst1; //a cada novo nó, recebe o inicio da lista principal
        Lista* aux = lst1->prox; //recebe o próximo nó da lista

        while(aux != NULL){

            if(ComparaDatas(aux->m->data, lst2->m->data) < 0) //os conteúdos referentes as datas da lista são comparados
                lst2 = aux; // recebe o próximo nó da lista

            aux = aux->prox;
        }

        if(lst2 != lst1)
            Trocar(lst1, lst2); //troca os medicamento de lugar na lista

        lst1 = lst1->prox;
    }
    return lista;
}

Lista* OrdenaListaValor(Lista* lista) {

    Lista* lst1 = lista;

    while(lst1 != NULL){

        Lista* lst2 = lst1->prox; //armazena o próximo nó da lista

        while(lst2 != NULL){

            if(lst1->m->valor > lst2->m->valor) //se o valor da lista for maior que o valor so próximo nó, os medicamentos são trocados
                Trocar(lst1, lst2);

            lst2 = lst2->prox;
        }
        lst1 = lst1->prox;
    }
    return lista;
}

void LiberaLista(Lista* lista){

    Lista* temp = NULL; //auxiliar

    while(lista != NULL){

        temp = lista->prox; //recebe o próximo nó
        free(lista->m); //memória do medicamento é liberada
        free(lista); //nó é liberado
        lista = temp; //recebe o próxmo nó
    }
}
