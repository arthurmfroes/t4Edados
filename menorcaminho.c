#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "menorcaminho.h"

#define INDEFINIDO -1
//dijkstra em pseudocodigo
// dijstra(grafo g, no inicial)
//   {
//     for (n = cada nó em g) {
//       visitado[n] = falso
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
//   }


void dijkstra(Grafo grafo, int origem, float* distancias, int* predecessores) {
    int nvertices = g_nvertices(grafo);
    bool* visitados = (bool*)malloc(nvertices * sizeof(bool));

    for (int i = 0; i < nvertices; i++) {
        distancias[i] = INT_MAX;
        predecessores[i] = 0;
        visitados[i] = false;
    }

    distancias[origem] = 0.0;

    for (int i = 0; i < nvertices; i++) {
        float menorDistancia = INT_MAX;
        int verticeAtual = -1;

        for (int j = 0; j < nvertices; j++) {
            if (!visitados[j] && distancias[j] < menorDistancia) {
                menorDistancia = distancias[j];
                verticeAtual = j;
            }
        }

        if (verticeAtual == -1) {
            break;
        }

        visitados[verticeAtual] = true;

        for (int j = 0; j < nvertices; j++) {
            float peso = g_peso_aresta(grafo, verticeAtual, j);
            if (peso > 0.0 && distancias[verticeAtual] + peso < distancias[j]) {
                distancias[j] = distancias[verticeAtual] + peso;
                predecessores[j] = verticeAtual;
            }
        }
    }

    free(visitados);
}

void EncontraMenorCaminho(Grafo g, listavertices lista_de_vertices) {

  int nvertices = g_nvertices(g);
  float* distancias = (float*)malloc(nvertices * sizeof(float));
  int* predecessores = (int*)malloc(nvertices * sizeof(int));

  listavisitas lista_de_visitas = NULL;

  lista_de_visitas = lerArquivoVisitas(lista_de_visitas, "visita.csv", lista_de_vertices);
  
  int proxvisita = 0;

  while (proxvisita != -1) {
    if (proxvisita == -1) {
      break;}
    proxvisita = retornaProxVisita(lista_de_visitas);
    printf("Proxima visita: %d\n", proxvisita);
  }

    int origem = 0;
    int i = 19;
    dijkstra(g, origem, distancias, predecessores);
    printf("Menor distancia do vertice %d ate %d: %.2f\n", origem, i, distancias[i]);
    printf("Caminho: %d", i);
    int v = i;
    while (v != origem) {
        printf(" <- %d", predecessores[v]);
        v = predecessores[v];
        
    // Liberação da memória do grafo
    free(distancias);
    free(predecessores);
    }
}
