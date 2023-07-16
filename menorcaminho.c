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

void printa_origem_destino(int id, listavertices lista_de_vertices, char *nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    double latitude = retornaLatitude(id, lista_de_vertices);
    double longitude = retornaLongitude(id, lista_de_vertices);
    char *nome = retornaNome(id, lista_de_vertices);

    fprintf(arquivo, "%lf,%lf(%s);\n", latitude, longitude, nome);

    fclose(arquivo);
}

void printa_map (char* nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    fprintf(arquivo, "[map]\n");
    fclose(arquivo);
}

void printa_intermediarios (int* pai, listavertices lista_de_vertices, char *nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    for (int i = 0; i< retornaNumVertices(lista_de_vertices); i++) {
        if (pai[i] != -1) {
            double latitude = retornaLatitude(i, lista_de_vertices);
            double longitude = retornaLongitude(i, lista_de_vertices);
            char *nome = retornaNome(i, lista_de_vertices);
            fprintf(arquivo, "%lf,%lf ", latitude, longitude, nome);
        }
    }
    fclose(arquivo);
}

int* dijkstra(Grafo grafo, int origem) {
    int nvertices = g_nvertices(grafo);
    float* distancias = (float*)malloc(nvertices * sizeof(float));
    int* predecessores = (int*)malloc(nvertices * sizeof(int));
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
    free(distancias);
    return predecessores;
}

void EncontraMenorCaminho(Grafo g, listavertices lista_de_vertices) {
    int numVisitas = 0;
    int* lista_de_visitas = lerArquivoVisitas(&numVisitas, "visita.csv", lista_de_vertices);
    char* nome_Arquivo = "menorcaminho.txt";
    for (int i = 0; i<numVisitas; i++) {
        printf("%d\n", lista_de_visitas[i]);
    }
  


    int* pai;
    int i = 0;
    int ultima;

    printa_map(nome_Arquivo);
    printa_origem_destino(lista_de_visitas[0], lista_de_vertices, nome_Arquivo);
    pai = dijkstra(g, lista_de_visitas[i]);
    printa_intermediarios(pai, lista_de_vertices, nome_Arquivo);


}
