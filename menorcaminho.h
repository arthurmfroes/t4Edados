#ifndef MENORCAMINHO_H
#define MENORCAMINHO_H

#include "grafo.h"

void EncontraMenorCaminho(Grafo g);
void dijkstra(Grafo grafo, int origem, float* distancias, int* predecessores);

#endif