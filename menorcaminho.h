#ifndef MENORCAMINHO_H
#define MENORCAMINHO_H

#include "grafo.h"

void EncontraMenorCaminho(Grafo g);
void dijkstra(Grafo g, int inicial, float *distancia, int *pai);


#endif