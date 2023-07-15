#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "menorcaminho.h"

#define INFINITO INT_MAX
#define INDEFINIDO -1

void dijkstra(Grafo g, int inicial, float *distancia, int *pai)
{
    printf("Dijkstra\n");
    int n, a, d;
    float n_dist;
    int num_vertices = g_nvertices(g);
    bool visitado[num_vertices];
    for (n = 0; n < num_vertices; n++) {
        visitado[n] = false;
        distancia[n] = INFINITO;
        pai[n] = INDEFINIDO;
    }
    distancia[inicial] = 0;
    while (true) {
        int menor_distancia = INFINITO;
        int menor_distancia_vertice = -1;
        for (n = 0; n < num_vertices; n++) {
            if (!visitado[n] && distancia[n] < menor_distancia) {
                menor_distancia = distancia[n];
                menor_distancia_vertice = n;
            }
        }
        if (menor_distancia_vertice == -1)
            break;
        visitado[menor_distancia_vertice] = true;
        g_arestas_que_partem(g, menor_distancia_vertice);
        while (g_proxima_aresta(g, NULL, &d, &n_dist)) {
            if (!visitado[d]) {
                int distancia_atualizada = distancia[menor_distancia_vertice] + n_dist;
                if (distancia_atualizada < distancia[d]) {
                    distancia[d] = distancia_atualizada;
                    pai[d] = menor_distancia_vertice;
                }
            }
        }
    }
    printf("Fim Dijkstra\n");
}

void EncontraMenorCaminho(Grafo g)
{
    // Exemplo de uso

    int num_vertices = g_nvertices(g);

    float distancia[num_vertices];
    int pai[num_vertices];

    //dijkstra(g, 0, distancia, pai);
    g_arestas(g);
    int destino = 0;
    int origem = 0;
    float peso = 0;
    bool eh_aresta = true;
    while (eh_aresta == true) {
        eh_aresta = g_proxima_aresta(g, &destino, &origem, &peso);
        printf("%d -> %d (%f)\n", origem, destino, peso);
    }

    // Imprime os resultados
    printf("Distancias a partir do no 0:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("No %d: %lf\n", i, distancia[i]);
    }

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