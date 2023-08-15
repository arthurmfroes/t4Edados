#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leituras.h"
#include "grafo.h"

#define TAM_MAX_LINHA 90


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
    int numArestas;
    struct _arestas* aresta;
    struct _listaarestas* prox;
};

listavertices carregaVertices(listavertices lista, const char* nomeArquivo) {
    vertices novoVertice = NULL;
    listavertices novoNo = NULL;
    listavertices ultimoNo = NULL;

    FILE* arquivo = fopen(nomeArquivo, "r");

    char linha[100];
    int id = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#') {
            continue;  // Ignorar linhas que começam com '#'
        }

        linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha


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

        novoVertice->desc = (desc != NULL) ? malloc(strlen(desc) + 1) : malloc(14); // Aloca memória para a string desc
        
        if (lista == NULL) {
            lista = (listavertices)malloc(sizeof(struct _listavertices));
            lista->local = novoVertice;
            lista->prox = NULL;
            ultimoNo = lista;
        } else {
            novoNo = (listavertices)malloc(sizeof(struct _listavertices));
            novoNo->local = novoVertice;
            novoNo->prox = NULL;
            ultimoNo->prox = novoNo;
            ultimoNo = novoNo;}

        id++;
    }
    fclose(arquivo);
    return lista;
}



// Função para ler e armazenar a lista de caminhos
listaarestas lerArquivoArestas(listaarestas listaAresta, const char* nomeArquivo, listavertices listaLocais) {
    FILE* arquivo = fopen(nomeArquivo, "r");

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
        listavertices atual = listaLocais;
        while (atual != NULL) {
            if (strcmp(atual->local->nome, origemStr) == 0)
                origemID = atual->local->id;
            else if (strcmp(atual->local->nome, destinoStr) == 0)
                destinoID = atual->local->id;

            if (origemID != -1 && destinoID != -1)
                break;

            atual = atual->prox;
        }
        if (origemID != -1 && destinoID != -1) {
            arestas novaAresta = (arestas)malloc(sizeof(struct _arestas));
            novaAresta->origem = origemID;
            novaAresta->destino = destinoID;
            novaAresta->distancia = atualizarDistancia(origemID, destinoID, listaLocais);
            
            listaarestas novoNo = (listaarestas)malloc(sizeof(struct _listaarestas));
            novoNo->aresta = novaAresta;
            novoNo->prox = NULL;

            if (listaAresta == NULL) {
                listaAresta = novoNo;
            } else {
                listaarestas atual = listaAresta;
                while (atual->prox != NULL)
                    atual = atual->prox;
                atual->prox = novoNo;
            }
        }
    }
    fclose(arquivo);
    return listaAresta;
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
    double distLO = difLon * cos(origemVertice->local->latitude) * (10000.0 / 90.0); // Distância leste-oeste

    // Calcula a distância total como a hipotenusa do triângulo formado
    double distancia = sqrt(distNS * distNS + distLO * distLO);
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

int retornaNumVertices (listavertices listaLocais) {
    int numVertices = 0;
    listavertices atual = listaLocais;
    while (atual != NULL) {
        numVertices++;
        atual = atual->prox;
    }
    return numVertices;
}

int* lerArquivoVisitas(int* numVisitas, char* nomearquivo, listavertices vertices) {
    FILE* arquivo = fopen(nomearquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char linha[6];
    int capacidade = 10; // Capacidade inicial do vetor
    int* visitas = (int*)malloc(capacidade * sizeof(int));
    int count = 0; // Contador de visitas

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove o caractere de nova linha

        // Procura o vértice com o nome correspondente na lista de vértices
        listavertices atual = vertices;
        while (atual != NULL) {
            if (strcmp(atual->local->nome, linha) == 0) {
                // Encontrou o vértice correspondente
                visitas[count++] = atual->local->id;

                // Redimensiona o vetor se necessário
                if (count >= capacidade) {
                    capacidade *= 2;
                    int* novoVisitas = (int*)realloc(visitas, capacidade * sizeof(int));
                    if (novoVisitas == NULL) {
                        printf("Erro ao redimensionar o vetor de visitas.\n");
                        fclose(arquivo);
                        free(visitas);
                        return NULL;
                    }
                    visitas = novoVisitas;
                }

                break;
            }
            atual = atual->prox;
        }
    }

    fclose(arquivo);
    *numVisitas = count;
    return visitas;
}

double retornaLatitude (int id, listavertices listaLocais) {
    listavertices atual = listaLocais;
    while (atual != NULL) {
        if (atual->local->id == id)
            return atual->local->latitude;
        atual = atual->prox;
    }
    return 0.0;
}
double retornaLongitude (int id, listavertices listaLocais) {
    listavertices atual = listaLocais;
    while (atual != NULL) {
        if (atual->local->id == id)
            return atual->local->longitude;
        atual = atual->prox;
    }
    return 0.0;
}
char* retornaNome (int id, listavertices listaLocais) {
    listavertices atual = listaLocais;
    while (atual != NULL) {
        if (atual->local->id == id)
            return atual->local->nome;
        atual = atual->prox;
    }
    return NULL;
}
