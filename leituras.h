#ifndef LEITURAS_H
#define LEITURAS_H

#include "grafo.h"

typedef struct locais {
    int id;
    char* nome;
    double latitude;
    double longitude;
    char* desc;
} Locais;

typedef struct listalocais {
    Locais* local;
    struct ListaLocais* prox;
    struct ListaLocais* ant;
} ListaLocais;

typedef struct arestas {
    char* origem;
    char* destino;
    double distancia;
} Arestas;

typedef struct listaarestas {
    Arestas* aresta;
    struct listaarestas* prox;
    struct listaarestas* ant;
} ListaArestas;

void lerArquivoVertices(ListaLocais** listaLocais, const char* nomeArquivo, Grafo self);
void atualizarDistancia(Arestas* aresta, ListaLocais* listaLocais);
void lerArquivoArestas(ListaArestas** listaArestas, const char* nomeArquivo, ListaLocais* listaLocais);
void insereListasNoGrafo(Grafo grafo, ListaLocais* listaLocais, ListaArestas* listaArestas);

#endif  // LEITURAS_H
