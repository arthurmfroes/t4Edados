#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

struct _grafo {
    float matriz_arestas[MAX_VERTICES][MAX_VERTICES];
    bool orientado;
    int nvertices;
    int narestas;
    bool consulta_em_andamento;

    int tipo_consulta;
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
    self->narestas = 0;

    int tipo_consulta = -1;
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
    self->narestas++;
    self->matriz_arestas[origem][destino] = distancia;
}

// remove uma aresta do grafo
void g_rem_aresta(Grafo self, int origem, int destino) {
    self->matriz_arestas[origem][destino] = 0;
}

void g_arestas(Grafo self) {
    if (self == NULL)
        return;

    self->consulta_em_andamento = true;
    self->tipo_consulta = 0;
    self->arestas_consultadas = 0;
    self->prox_origem = 0;
    self->prox_destino = 0;
    self->prox_aresta = 0.0;
    printf("%d\n", self->narestas);
    // for (int i = 0; i < self->nvertices; i++) {
    //     for (int j = 0; j < self->nvertices; j++) {
    //         if (self->matriz_arestas[i][j] != 0) {
    //             //printf("%d %d %f\n", i, j, self->matriz_arestas[i][j]);
    //         }
    //     }
    // }
}

void g_arestas_que_partem(Grafo self, int origem) {
    if (self == NULL)
        return;

    self->tipo_consulta = 1;
    self->consulta_em_andamento = true;
    self->arestas_consultadas = 0;
    self->prox_origem = origem;
    self->prox_destino = 0;
    self->prox_aresta = self->matriz_arestas[origem][0];
}

bool g_proxima_aresta(Grafo self, int *origem, int *destino, float *peso) {
    if (self == NULL)
        return false;

    if (self->tipo_consulta == 0) { //consulta
        if (!self->consulta_em_andamento || self->arestas_consultadas == self->narestas)
            return false;

        // Percorre a matriz de arestas buscando a próxima aresta válida
        for (int i = self->prox_origem; i < self->nvertices; i++) {
            for (int j = self->prox_destino; j < self->nvertices; j++) {
                if (self->matriz_arestas[i][j] != 0.0) {
                    *origem = i;
                    *destino = j;
                    *peso = self->matriz_arestas[i][j];
                    self->arestas_consultadas++;
                    self->prox_origem = i;
                    self->prox_destino = j + 1;
                    self->prox_aresta = self->matriz_arestas[i][j + 1];
                    return true;
                }
            }
            self->prox_destino = 0;  // Reinicia a busca para a próxima linha
        }

        // Se chegou até aqui, significa que não há mais arestas a serem consultadas
        self->consulta_em_andamento = false;
        self->arestas_consultadas = 0;
        self->tipo_consulta = -1;
        return false;

    } else if (self->tipo_consulta == 1) {
        // Consulta das arestas que partem da origem especificada

        if (!self->consulta_em_andamento || self->arestas_consultadas == self->nvertices)
            return false;

        while (self->prox_destino < self->nvertices) {
            if (self->matriz_arestas[self->prox_origem][self->prox_destino] != 0.0) {
                *origem = self->prox_destino;//mudar a ordem, fiz gambiarra
                *destino = self->prox_origem;//mudar a ordem, fiz gambiarra
                *peso = self->matriz_arestas[self->prox_origem][self->prox_destino];
                self->arestas_consultadas++;
                self->prox_destino++;
                self->prox_aresta = self->matriz_arestas[self->prox_origem][self->prox_destino];
                return true;
            }
            self->prox_destino++;
        }

        // Se chegou até aqui, significa que não há mais arestas a serem consultadas
        self->consulta_em_andamento = false;
        self->arestas_consultadas = 0;
        self->tipo_consulta = -1;
        return false;
    }

    return false;
}







