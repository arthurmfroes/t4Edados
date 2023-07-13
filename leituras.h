#ifndef LEITURAS_H
#define LEITURAS_H

#include "grafo.h"

typedef struct _vertices *vertices;
typedef struct _listavertices *listavertices;
typedef struct _arestas *arestas;
typedef struct _listaarestas *listaarestas;

//Carrega lista de vertices e cria o grafo com n vertices e orientado ou nao
listavertices carregaVertices(listavertices vertices, const char* nomeArquivo);
//void atualizarDistancia(Arestas* aresta, ListaLocais* listaLocais);

//cria lista de arestas
listaarestas lerArquivoArestas(listaarestas arestas, const char* nomeArquivo, listavertices vertices);

//insere lista de arestas no grafo
void insereListasNoGrafo(Grafo grafo, listaarestas arestas);


//função interna para atualizar a distancia entre dois locais, não é chamada diretamente
double atualizarDistancia(int origem, int destino, listavertices listaLocais);

int retornaNumVertices (listavertices listaLocais);

#endif  // LEITURAS_H
