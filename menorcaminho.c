#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "menorcaminho.h"

#define INFINITO INT_MAX
#define INDEFINIDO -1

void dijkstra(Grafo g, int inicial) {
    printf("Dijkstra\n");
  int n;
  int distancia[MAX_VERTICES];
  int pai[MAX_VERTICES];
  bool visitado[MAX_VERTICES];

  for (n = 0; n < g_nvertices(g); n++) {
    visitado[n] = false;
    distancia[n] = INFINITO;
    pai[n] = INDEFINIDO;
  }

  distancia[inicial] = 0;

  while (tem_nao_visitado(visitado, g_nvertices(g))) {
    int n = encontrar_menor_distancia(distancia, visitado, g_nvertices(g));
    visitado[n] = true;
    g_arestas_que_partem(g, n);
    int origem, destino;
    float peso;

    while (g_proxima_aresta(g, &origem, &destino, &peso)) {
      int n_dist = distancia[n] + peso;
      if (n_dist < distancia[destino]) {
        distancia[destino] = n_dist;
        pai[destino] = n;
      }
    }
  }

  // Retorne a distância e o pai (anterior) de cada nó.
  // Implemente o código apropriado para retornar esses valores.
}

bool tem_nao_visitado(bool visitado[], int num_vertices) {
  for (int i = 0; i < num_vertices; i++) {
    if (!visitado[i]) {
      return true;
    }
  }
  return false;
}

int encontrar_menor_distancia(int distancia[], bool visitado[], int num_vertices) {
    printf("Encontrar menor distancia\n");
  int menor_distancia = INFINITO;
  int menor_no = -1;

  for (int i = 0; i < num_vertices; i++) {
    if (!visitado[i] && distancia[i] < menor_distancia) {
      menor_distancia = distancia[i];
      menor_no = i;
    }
  }

  return menor_no;
}


void EncontraMenorCaminho(Grafo g)
{
    // Exemplo de uso

    int num_vertices = g_nvertices(g);

    float distancia[num_vertices];
    int pai[num_vertices];

    dijkstra(g, 0);
    
    g_arestas(g);
    int destino;
    int origem;
    float peso;
    bool eh_aresta = true;
    // while (eh_aresta == true) {
    //     eh_aresta = g_proxima_aresta(g, &destino, &origem, &peso);
    //     if (eh_aresta == false)
    //         break;
    //     printf("%d -> %d (%f)\n", origem, destino, peso);
    // }

    g_arestas_que_partem(g, 6);
    eh_aresta = true;
    while (eh_aresta == true) {
        eh_aresta = g_proxima_aresta(g, &destino, &origem, &peso);
        if (eh_aresta == false)
            break;
        printf("%d -> %d (%f)\n", origem, destino, peso);
    }

    // // Imprime os resultados
    // printf("Distancias a partir do no 0:\n");
    // for (int i = 0; i < num_vertices; i++) {
    //     printf("No %d: %lf\n", i, distancia[i]);
    // }

}
//traduzir isso aqui:
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