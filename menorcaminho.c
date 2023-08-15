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

    fprintf(arquivo, "%lf,%lf(%s)", latitude, longitude, nome);

    fclose(arquivo);
}

void printa_newline (char* nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    fprintf(arquivo, ";\n");
    fclose(arquivo);
}
void printa_map_fechamento (char* nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    fprintf(arquivo, "\n[/map]");
    fclose(arquivo);
}

void printa_map (char* nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    fprintf(arquivo, "[map]\n");
    fclose(arquivo);
}

void printa_intermediarios (int id, listavertices lista_de_vertices, char *nome_Arquivo) {
    FILE *arquivo = fopen(nome_Arquivo, "a");
    double latitude = retornaLatitude(id, lista_de_vertices);
    double longitude = retornaLongitude(id, lista_de_vertices);
    char *nome = retornaNome(id, lista_de_vertices);
    fprintf(arquivo, "%lf,%lf ", latitude, longitude);

    fclose(arquivo);
}

int* dijkstra(Grafo grafo, int origem) {
    int numVertices = g_nvertices(grafo);


    float* distancias = (float*)malloc(numVertices * sizeof(float));
    int* pai = (int*)malloc(numVertices * sizeof(int));
    bool* visitados = (bool*)malloc(numVertices * sizeof(bool));


    for (int i = 0; i < numVertices; i++) {
        visitados[i] = false;
        distancias[i] = INT_MAX;
        pai[i] = 0;
    }

    distancias[origem] = 0;
    float menorDistancia;
    int vertice;
    float peso;

    for (int i = 0; i < numVertices; i++) {
        menorDistancia = INT_MAX;
        vertice = -1;

        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && distancias[j] < menorDistancia) {
                menorDistancia = distancias[j];
                vertice = j;
            }
        }

        if (vertice == -1) {
            break;
        }

        visitados[vertice] = true;

        for (int j = 0; j < numVertices; j++) {
            peso = g_dist_aresta(grafo, vertice, j);
            if (peso > 0 && distancias[vertice] + peso < distancias[j]) {
                distancias[j] = distancias[vertice] + peso;
                pai[j] = vertice;
            }
        }
    }

    free(visitados);

    free(distancias);
    
    return pai;
}

void printPath(int* pai, int destino, listavertices lista_de_vertices, char *nome_Arquivo) {
    if (pai[destino] == 0) {
        printa_intermediarios(destino, lista_de_vertices, nome_Arquivo);
        return;
    } else {
        printPath(pai, pai[destino], lista_de_vertices, nome_Arquivo);
        printa_intermediarios(destino, lista_de_vertices, nome_Arquivo);
    }
}

void EncontraMenorCaminho(Grafo g, listavertices lista_de_vertices) {
    int numVisitas = 0;
    int* lista_de_visitas = lerArquivoVisitas(&numVisitas, "visita.csv", lista_de_vertices);
    char* nome_Arquivo = "menorcaminho.txt";

    int* pai;
    int nvertices = g_nvertices(g);

    printa_map(nome_Arquivo);
    printa_origem_destino(lista_de_visitas[0], lista_de_vertices, nome_Arquivo);
        printa_newline(nome_Arquivo);
    for (int i = 0; i<numVisitas - 1; i++) {
        pai = dijkstra(g, lista_de_visitas[i]);
        printPath(pai, lista_de_visitas[i+1], lista_de_vertices, nome_Arquivo);
    }
    printa_newline(nome_Arquivo);
    printa_origem_destino(lista_de_visitas[numVisitas-1], lista_de_vertices, nome_Arquivo);
    printa_map_fechamento(nome_Arquivo);

    free(lista_de_visitas);
}

