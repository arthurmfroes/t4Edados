#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


// aloca e inicializa um grafo com n vértices
// o grafo pode ser orientado ou não (afeta o processamento das arestas)
// retorna um ponteiro para o grafo alocado
Grafo g_cria(int n, bool orientado){
    Grafo self = (Grafo) malloc(sizeof(struct _grafo));
    int i, j;
    i = 0;
    j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            self->matriz_arestas[i][j] = 0;
        }
    }
    self->orientado = orientado;
    self->nvertices = n;

    return self;
}

// libera a memória usada pelo grafo
void g_destroi(Grafo self){
    free(self);
}

// retorna o número de vértices do grafo
int g_nvertices(Grafo self){
    return self->nvertices;
}

// insere uma aresta no grafo (ou altera o peso de uma aresta já existente)
void g_ins_aresta(Grafo self, int origem, int destino, float distancia){
    self->matriz_arestas[origem][destino] = distancia;
}

// remove uma aresta do grafo
void g_rem_aresta(Grafo self, int origem, int destino) {
    self->matriz_arestas[origem][destino] = 0;
}

// inicia uma consulta a arestas do grafo.
// as próximas chamadas a g_proxima_aresta devem retornar cada aresta do grafo
void g_arestas(Grafo self) {
    int origem = 0;
    int destino = 0;
    bool controle = true;


    printf("\nArestas do grafo:\n");
    for (origem = 0; origem < self->nvertices; origem++) {
        for (destino = 0;destino < self->nvertices; destino++) {
            controle = g_proxima_aresta(self, &origem, &destino, NULL);
        }
    }
}

// inicia uma consulta a arestas do grafo.
// as próximas chamadas à g_proxima_aresta devem retornar cada aresta do grafo que parte do vértice origem
void g_arestas_que_partem(Grafo self, int origem) {
    if (origem >= 0 && origem < self->nvertices) {
        printf("Arestas que partem do vértice %d:\n", origem);
        for (int i = 0; i < self->nvertices; i++) {
            if (self->matriz_arestas[origem][i] != 0) {
                printf("%d -> %d\n", origem, i);
            }
        }
    } else {
        printf("Vértice inválido!\n");
    }
}


// retorna os dados sobre a próxima aresta de uma consulta
// retorna true se ok ou false se não tem mais arestas ou se não foi iniciada uma consulta
// cada ponteiro pode ser NULL, para o caso de não se estar interessado na informação associada
// não se deve inserir ou remover arestas no grafo com uma consulta em andamento
bool g_proxima_aresta(Grafo self, int *origem, int *destino, float *peso) {
    if (*origem < self->nvertices && *destino < self->nvertices) {
        if (self->matriz_arestas[*origem][*destino] == 0) {
            return true;
        } else {
            printf("%d -> %d (%.2f)\n", *origem, *destino, self->matriz_arestas[*origem][*destino]);
            return true;
        }
    }
    return false;
}