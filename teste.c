#include <stdio.h>
#include <stdlib.h>
#include "leituras.h"

void imprimirLista(ListaLocais* lista) {
    ListaLocais* atual = lista;

    while (atual != NULL) {
        printf("ID: %d\n", atual->local->id);
        printf("Nome: %s\n", atual->local->nome);
        printf("Latitude: %lf\n", atual->local->latitude);
        printf("Longitude: %lf\n", atual->local->longitude);
        printf("Descrição: %s\n", atual->local->desc);
        printf("---------------------\n");

        atual = atual->prox;
    }
}

void imprimirArestas(ListaArestas* listaarestas) {
    ListaArestas* atual = listaarestas;
    printf("Chegou aqui");
    while (atual != NULL) {
        printf("Origem: %s\n", atual->aresta->origem);
        printf("Destino: %s\n", atual->aresta->destino);
        printf("Distancia: %lf\n", atual->aresta->distancia);
        printf("---------------------\n");

        atual = atual->prox;
    }
}

int main() {
    ListaLocais* lista = NULL;
    ListaArestas* listaarestas = NULL;
    lerArquivoVertices(&lista, "locais.csv"); //inicializa a lista de locais e armazena todo conteudo do arquivo nela
    lerArquivoArestas(&listaarestas, "caminhos.csv", lista); //inicializa a lista de arestas e armazena todo conteudo do arquivo nela
    imprimirLista(lista);
    imprimirArestas(listaarestas);

    // Liberar memória alocada para a lista de locais
    ListaLocais* atual = lista;
    while (atual != NULL) {
        ListaLocais* proximo = atual->prox;
        free(atual->local->nome);
        free(atual->local->desc);
        free(atual->local);
        free(atual);
        atual = proximo;
    }

    ListaArestas* atualArestas = listaarestas;
    while (atualArestas != NULL) {
        ListaArestas* proximoArestas = atualArestas->prox;
        free(atualArestas->aresta->origem);
        free(atualArestas->aresta->destino);
        free(atualArestas->aresta);
        free(atualArestas);
        atualArestas = proximoArestas;
    }

    return 0;
}
