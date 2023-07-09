#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "menorcaminho.h"

// Etapas:

// ler arquivo de visita

// procurar locais na lista de vertices e armazenar ids

// enviar local para a funcao de menor caminho

// imprimir menor caminho em arquivo

#define INFINITY 999999


void lerArquivoTexto(const char *nomeArquivo, char **linhas) {
    FILE *arquivo;
    char linha[6]; // Tamanho máximo de uma linha

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '\0') {
            break;
        }
        linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha

        linhas[i] = malloc(strlen(linha) + 1);
        strcpy(linhas[i], linha);
        i++;
    }
        for (int j = 0; j < i; j++) {
            printf("%s\n", linhas[j]);
        }
    fclose(arquivo);
}

void criarVetorDeVisitas(char **linhas, ListaLocais *listalocais, int visitas[MAX_VISITAS]) {

        for (int i = 0; i < MAX_VISITAS; i++) {
            ListaLocais *lista = listalocais;
            while (lista != NULL) {
                if (strcmp(lista->local->nome, linhas[i]) == 0) {
                    visitas[i] = lista->local->id;
                    break;
                } else {
                lista = lista->prox; }
            }
        }
}

void dijkstra(Grafo self, ListaLocais* listaLocais){
    int i, j;
    char *linhas_Visitadas[MAX_VISITAS];
    int vetor_visitas[MAX_VISITAS];

    lerArquivoTexto("visita.csv", linhas_Visitadas);

    printf("saiu do ler arquivo\n");

    for (int i = 0; i < MAX_VISITAS; i++) {
            ListaLocais *lista = listaLocais;
            while (lista != NULL) {
                if (strcmp(lista->local->nome, linhas_Visitadas[i]) == 0) {
                    vetor_visitas[i] = lista->local->id;
                    printf("id: %d\n", vetor_visitas[i]);
                    break;
                } else {
                lista = lista->prox; }
            }
    }
    printf("saiu do vetor de visitas\n");

    dijkstraCalcula(self, vetor_visitas[0], vetor_visitas[1], vetor_visitas[2], listaLocais);

  
}


void dijkstraCalcula(Grafo g, int origem, int intermediario, int destino, ListaLocais* listaLocais) {
    float distancias[MAX_VERTICES];
    int predecessores[MAX_VERTICES];
    bool visitados[MAX_VERTICES];

    // Inicializa os arrays de distâncias, predecessores e visitados
    for (int i = 0; i < g->nvertices; i++) {
        distancias[i] = INFINITY;
        predecessores[i] = -1;
        visitados[i] = false;
    }

    // Define a distância da origem como 0
    distancias[origem] = 0;

    // Loop principal
    for (int i = 0; i < g->nvertices - 1; i++) {
        // Encontra o vértice não visitado com a menor distância
        int u = -1;
        float menor_distancia = INFINITY;

        for (int j = 0; j < g->nvertices; j++) {
            if (!visitados[j] && distancias[j] < menor_distancia) {
                u = j;
                menor_distancia = distancias[j];
            }
        }

        // Marca o vértice como visitado
        visitados[u] = true;

        // Atualiza as distâncias dos vértices adjacentes ao vértice atual
        for (int v = 0; v < g->nvertices; v++) {
            if (!visitados[v] && g->matriz_arestas[u][v] > 0 && distancias[u] + g->matriz_arestas[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + g->matriz_arestas[u][v];
                predecessores[v] = u;
            }
        }
    }

    // Verifica se o caminho entre origem, intermediário e destino existe
    if (distancias[intermediario] == INFINITY || distancias[destino] == INFINITY) {
        printf("Caminho inexistente.\n");
        return;
    }

    // Constrói o caminho entre origem, intermediário e destino
    int caminho[MAX_VERTICES];
    int contador = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[contador] = atual;
        atual = predecessores[atual];
        contador++;
    }

    // Imprime o menor caminho
    printf("Menor caminho: \n");

    printf("[MAP]\n");

        ListaLocais *listaAtual = listaLocais;
        while (listaAtual != NULL) {
            if (listaAtual->local->id == caminho[0]) {
                printf("%lf,", listaAtual->local->latitude);
                printf("%lf", listaAtual->local->longitude);
                printf("(%s)", listaAtual->local->nome);
                printf(";\n");
                break;
            }
            listaAtual = listaAtual->prox;
        }
    
    for (int i = 0; i < contador; i++) {
        ListaLocais *listaAtual = listaLocais;
        while (listaAtual != NULL) {
            if (listaAtual->local->id == caminho[i]) {
                printf("%lf,", listaAtual->local->latitude);
                printf("%lf ", listaAtual->local->longitude);
                break;
            }
            listaAtual = listaAtual->prox;
        }
    }
        ListaLocais *listaAtual = listaLocais;
        while (listaAtual != NULL) {
            if (listaAtual->local->id == caminho[contador - 1]) {
                printf("%lf,", listaAtual->local->latitude);
                printf("%lf", listaAtual->local->longitude);
                printf("(%s)", listaAtual->local->nome);
                printf(";\n");
                break;
            }
            listaAtual = listaAtual->prox;
        }
    
}


