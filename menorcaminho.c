#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include "menorcaminho.h"


#define INFINITO 999999999
#define INDEFINIDO -1

// dijstra(Grafo g, int inicial)
// {
//     int n, a, d, n_dist;
//     int num_vertices = g_numVertices(g);
//     bool visitado[num_vertices];
//     int distancia[num_vertices];
//     int pai[num_vertices];
//     for (n = 0; n < num_vertices; n++) {
//       visitado[n] = false;
//       distancia[n] = INFINITO;
//       pai[n] = INDEFINIDO;
//     }
//     distancia[inicial] = 0;
//     while (tem nó não visitado) {
//       n = nó não visitado com menor distancia;
//       visitado[n] = true;
//       for (a = cada aresta que parte de n) {
//         d = destino(a);
//         n_dist = distancia[n] + peso(a);
//         if (n_dist < distancia[d]) {
//           distancia[d] = n_dist;
//           pai[d] = n;
//         }
//       }
//     }

//     return distancia, pai;
// }