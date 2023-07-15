#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

struct _grafo {
    float matriz_arestas[MAX_VERTICES][MAX_VERTICES];
    bool orientado;
    int nvertices;
    bool consulta_em_andamento;

    int arestas_consultadas;
    int prox_origem;//nao tenho ctz, verificar
    int prox_destino;//nao tenho ctz, verificar
    double prox_aresta;//nao tenho ctz, verificar
};

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

    self->consulta_em_andamento = false;
    self->prox_origem = -1;
    self->prox_destino = -1;
    self->prox_aresta = 0;

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

// retorna true se o grafo é orientado ou false caso contrário
bool g_orientado(Grafo self) {
    return self->orientado;
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
    self->consulta_em_andamento = true;
    self->prox_origem = 0;
    self->prox_destino = 0;
    self->prox_aresta = 0;
}

// inicia uma consulta a arestas do grafo.
// as próximas chamadas à g_proxima_aresta devem retornar cada aresta do grafo que parte do vértice origem
void g_arestas_que_partem(Grafo self, int origem) {
    self->consulta_em_andamento = true;
    self->prox_origem = origem;
    self->prox_destino = 0;
    self->prox_aresta = 0;
}

// retorna os dados sobre a próxima aresta de uma consulta
// retorna true se ok ou false se não tem mais arestas ou se não foi iniciada uma consulta
// cada ponteiro pode ser NULL, para o caso de não se estar interessado na informação associada
// não se deve inserir ou remover arestas no grafo com uma consulta em andamento
bool g_proxima_aresta(Grafo self, int *origem, int *destino, float *peso) {
    if (!self->consulta_em_andamento) {
        return false; // no ongoing query
    }

    while (self->prox_origem < self->nvertices) {
        for (int i = self->prox_destino; i < self->nvertices; i++) {
            if (self->matriz_arestas[self->prox_origem][i] != 0) {
                *origem = self->prox_origem;
                *destino = i;
                *peso = self->matriz_arestas[self->prox_origem][i];
                self->prox_destino = i + 1;

                if (self->prox_destino == self->nvertices) {
                    self->prox_destino = 0;
                    self->prox_origem++;
                }

                return true;
            }
        }

        self->prox_destino = 0;
        self->prox_origem++;
    }

    // No more edges or query not initiated
    self->consulta_em_andamento = false;
    return false;
}
