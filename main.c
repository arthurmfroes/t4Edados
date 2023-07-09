#include <stdio.h>
#include <stdlib.h>
#include "leituras.h"
#include "grafo.h"
#include "menorcaminho.h"


//função de controle
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

//função de controle
void imprimirArestas(ListaArestas* listaarestas) {
    ListaArestas* atual = listaarestas;
    while (atual != NULL) {
        printf("Origem: %s\n", atual->aresta->origem);
        printf("Destino: %s\n", atual->aresta->destino);
        printf("Distancia: %lf\n", atual->aresta->distancia);
        printf("---------------------\n");

        atual = atual->prox;
    }
}


//função de controle
void imprimirGrafo(Grafo grafo) {
    int nvertices = grafo->nvertices;
    
    printf("Grafo:\n");
    printf("vertices: %d\n", nvertices);
    printf("orientado: %s\n", grafo->orientado ? "sim" : "nao");
    
    printf("matriz:\n");
    for (int i = 0; i < nvertices; i++) {
        for (int j = 0; j < nvertices; j++) {
            printf("%.2f\t", grafo->matriz_arestas[i][j]);
        }
        printf("\n");
    }
}

int main() {
    ListaLocais* listavertices = NULL;
    ListaArestas* listaarestas = NULL;
    Grafo self = g_cria(MAX_VERTICES, false);
    lerArquivoVertices(&listavertices, "locais.csv", self); //inicializa a lista de locais e armazena todo conteudo do arquivo nela
    lerArquivoArestas(&listaarestas, "caminhos.csv", listavertices); //inicializa a lista de arestas e armazena todo conteudo do arquivo nela

    insereListasNoGrafo(self, listavertices, listaarestas);

    g_arestas_que_partem(self, 3);
    g_arestas_que_partem(self, 2);
    g_arestas_que_partem(self, 6);

    g_arestas(self);



    determinaMenorCaminho(self, listavertices);

    // Liberar memória alocada para a lista de locais
    ListaLocais* atual = listavertices;
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
