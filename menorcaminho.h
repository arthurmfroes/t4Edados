#ifndef MENORCAMINHO_H
#define MENORCAMINHO_H

#include "grafo.h"
#include "leituras.h"

void EncontraMenorCaminho(Grafo g, listavertices lista_de_vertices);

int* dijkstra(Grafo grafo, int origem);

void printa_origem_destino(int id, listavertices lista_de_vertices, char *nome_Arquivo);

void printa_map(char* nome_Arquivo);

void printa_intermediarios (int id, listavertices lista_de_vertices, char *nome_Arquivo);

void printPath(int* pai, int destino, listavertices lista_de_vertices, char *nome_Arquivo);

void printa_newline (char* nome_Arquivo);


#endif