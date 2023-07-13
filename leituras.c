#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leituras.h"
#include "grafo.h"

#define M_PI 3.14159265358979323846
#define TAM_MAX_LINHA 90
#define R 6371.0

struct _vertices {
    int id;
    char* nome;
    double latitude;
    double longitude;
    char* desc;
};

struct _listavertices {
    struct _vertices* local;
    struct _listavertices* prox;
};

struct _arestas {
    int origem;
    int destino;
    double distancia;
};

struct _listaarestas {
    struct _arestas* aresta;
    struct _listaarestas* prox;
};


int carregaVertices(listavertices lista, const char* nomeArquivo) {

    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[100];
    int id = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#') {
            continue;  // Ignorar linhas que começam com '#'
        }
        char* nome = strtok(linha, ",");
        char* latitudeStr = strtok(NULL, ",");
        char* longitudeStr = strtok(NULL, ",");
        char* desc = strtok(NULL, ",");

        if (nome == NULL || latitudeStr == NULL || longitudeStr == NULL) {
            printf("Formato inválido da linha: %s", linha);
            continue;
        }

        double latitude = strtod(latitudeStr, NULL);
        double longitude = strtod(longitudeStr, NULL);
        vertices novoVertice = (vertices)malloc(sizeof(struct _vertices));
        novoVertice->id = id;
        novoVertice->nome = strdup(nome);
        novoVertice->latitude = latitude;
        novoVertice->longitude = longitude;
        novoVertice->desc = (desc != NULL) ? strdup(desc) : strdup(" ");

        listavertices novoNo = (listavertices)malloc(sizeof(struct _listavertices));
        novoNo->local = novoVertice;
        novoNo->prox = NULL;

        if (lista == NULL) {
            lista= novoNo;
        } else {
            listavertices ultimo = lista;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        id++;
        }
    }
    if (id == 0) {
        printf("Nenhum local encontrado no arquivo.\n");
    }
    if (lista==NULL) {
        printf("Lista vazia.\n");
    }
    fclose(arquivo);
    return id;
}



// Função para ler e armazenar a lista de caminhos
void lerArquivoArestas(listaarestas listaAresta, const char* nomeArquivo, listavertices listaLocais) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#')
            continue;

        char* origemStr = strtok(linha, ",");
        char* destinoStr = strtok(NULL, ",");

        origemStr[strcspn(origemStr, "\r\n")] = '\0'; // Remove o caractere de nova linha
        destinoStr[strcspn(destinoStr, "\r\n")] = '\0'; // Remove o caractere de nova linha

        // Converte os nomes em IDs
        int origemID = -1, destinoID = -1;
        listavertices current = listaLocais;
        while (current != NULL) {
            printf("procurando ids");
            if (strcmp(current->local->nome, origemStr) == 0)
                origemID = current->local->id;
            else if (strcmp(current->local->nome, destinoStr) == 0)
                destinoID = current->local->id;

            if (origemID != -1 && destinoID != -1)
                break;

            current = current->prox;
        }

        // Cria uma nova aresta e a adiciona à lista de arestas
        if (origemID != -1 && destinoID != -1) {
            arestas novaAresta = (arestas)malloc(sizeof(struct _arestas));
            novaAresta->origem = origemID;
            novaAresta->destino = destinoID;
            novaAresta->distancia = atualizarDistancia(origemID, destinoID, listaLocais);
            printf("passou de atualizar distancia");
            listaarestas novaLista = (listaarestas)malloc(sizeof(struct _listaarestas));
            novaLista->aresta = novaAresta;
            novaLista->prox = NULL;

            if (listaAresta == NULL) {
                listaAresta = novaLista;
            } else {
                listaarestas atual = listaAresta;
                while (atual->prox != NULL)
                    atual = atual->prox;
                atual->prox = novaLista;
            }
        }
    }
    while (listaAresta != NULL) {
        printf("printando lista de arestas");
        printf("%d %d %lf\n", listaAresta->aresta->origem, listaAresta->aresta->destino, listaAresta->aresta->distancia);
        listaAresta = listaAresta->prox;
    }
    fclose(arquivo);
}

// Função para calcular a distância entre dois vértices
double atualizarDistancia(int origem, int destino, listavertices listaLocais) {
    listavertices origemVertice = listaLocais;
    listavertices destinoVertice = listaLocais;

    // Localiza os vértices de origem e destino na lista
    while (origemVertice != NULL) {
        if (origemVertice->local->id == origem)
            break;
        origemVertice = origemVertice->prox;
    }

    while (destinoVertice != NULL) {
        if (destinoVertice->local->id == destino)
            break;
        destinoVertice = destinoVertice->prox;
    }


    // Calcula a distância entre os vértices usando as coordenadas de latitude e longitude
    double difLat = origemVertice->local->latitude - destinoVertice->local->latitude;
    double difLon = origemVertice->local->longitude - destinoVertice->local->longitude;

    double distNS = difLat * (10000.0 / 90.0); // Distância norte-sul
    double distEW = difLon * cos(origemVertice->local->latitude) * (10000.0 / 90.0); // Distância leste-oeste

    // Calcula a distância total como a hipotenusa do triângulo formado
    double distancia = sqrt(distNS * distNS + distEW * distEW);
    printf("retornou a distancia %lf\n", distancia);
    return distancia * 1000.0;
}



void insereListasNoGrafo(Grafo grafo, listaarestas listaArestas) {
    // Insere as arestas no grafo
    listaarestas arestaAtual = listaArestas;
    bool orientado = g_orientado(grafo);
    if (arestaAtual == NULL) {
        return;
    }
    if (orientado == false) {
        while (arestaAtual != NULL) {
            g_ins_aresta(grafo, arestaAtual->aresta->origem, arestaAtual->aresta->destino, arestaAtual->aresta->distancia);
            g_ins_aresta(grafo, arestaAtual->aresta->destino, arestaAtual->aresta->origem, arestaAtual->aresta->distancia);
            arestaAtual = arestaAtual->prox;
        
        } 
    }else if (orientado == true) {
        while (arestaAtual != NULL) {
            g_ins_aresta(grafo, arestaAtual->aresta->origem, arestaAtual->aresta->destino, arestaAtual->aresta->distancia);
            arestaAtual = arestaAtual->prox;
        } 
    }
}


