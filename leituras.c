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

struct _listavisitas {
    int id;
    struct _listavisitas* prox;
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
        listavertices current = listaLocais;
        while (current != NULL) {
            if (strcmp(current->local->nome, origemStr) == 0)
                origemID = current->local->id;
            else if (strcmp(current->local->nome, destinoStr) == 0)
                destinoID = current->local->id;

            if (origemID != -1 && destinoID != -1)
                break;

            current = current->prox;
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
                listaarestas current = listaAresta;
                while (current->prox != NULL)
                    current = current->prox;
                current->prox = novoNo;
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
    double distEW = difLon * cos(origemVertice->local->latitude) * (10000.0 / 90.0); // Distância leste-oeste

    // Calcula a distância total como a hipotenusa do triângulo formado
    double distancia = sqrt(distNS * distNS + distEW * distEW);
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
    listavertices current = listaLocais;
    while (current != NULL) {
        numVertices++;
        current = current->prox;
    }
    return numVertices;
}

listavisitas lerArquivoVisitas(listavisitas visitas, char* nomearquivo, listavertices vertices) {
    FILE* arquivo = fopen(nomearquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    
    char linha[6];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove o caractere de nova linha
        
        // Procura o vértice com o nome correspondente na lista de vértices
        listavertices atual = vertices;
        while (atual != NULL) {
            if (strcmp(atual->local->nome, linha) == 0) {
                // Encontrou o vértice correspondente
                listavisitas novo = (listavisitas)malloc(sizeof(struct _listavisitas));
                novo->id = atual->local->id;
                novo->prox = NULL;
                
                if (visitas == NULL) {
                    visitas = novo;
                } else {
                    listavisitas ultimo = visitas;
                    while (ultimo->prox != NULL) {
                        ultimo = ultimo->prox;
                    }
                    ultimo->prox = novo;
                }
                
                break;
            }
            atual = atual->prox;
        }
        return visitas;
    }
    
    fclose(arquivo);
    while (visitas != NULL) {
        printf("Visita: %d\n", visitas->id);
        visitas = visitas->prox;
    }
}


int retornaProxVisita(listavisitas visitas) {
    if (visitas == NULL) {
        return -1;
    }

    listavisitas temp = visitas;
    int valor = temp->id;

    visitas = (visitas)->prox;
    free(temp);

    return valor;
}


