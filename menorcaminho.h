#ifndef MENORCAMINHO_H
#define MENORCAMINHO_H

#include "grafo.h"

void EncontraMenorCaminho(Grafo g);
void dijkstra(Grafo g, int inicial);
bool tem_nao_visitado(bool visitado[], int num_vertices);
int encontrar_menor_distancia(int distancia[], bool visitado[], int num_vertices);

#endif