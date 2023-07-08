#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leituras.h"

#define M_PI 3.14159265358979323846
#define TAM_MAX_LINHA 90
#define R 6371.0

void lerArquivoVertices(ListaLocais** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int id = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == '#' || linha[0] == '\n') {
            continue;  // Ignorar linhas que começam com "#" ou são vazias
        }

        // Remover quebra de linha no final da linha lida
        linha[strcspn(linha, "\n")] = '\0';

        // Tokenizar a linha usando a vírgula como delimitador
        char* token = strtok(linha, ",");
        if (token == NULL) {
            continue;  // Ignorar linhas inválidas sem campos
        }

        Locais* local = (Locais*)malloc(sizeof(Locais));
        local->id = id;
        id++;
        local->nome = strdup(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            free(local->nome);
            free(local);
            continue;  // Ignorar linhas inválidas sem latitude
        }
        local->latitude = strtod(token, NULL);

        token = strtok(NULL, ",");
        if (token == NULL) {
            free(local->nome);
            free(local);
            continue;  // Ignorar linhas inválidas sem longitude
        }
        local->longitude = strtod(token, NULL);

        token = strtok(NULL, ",");

        local->desc = strdup(token);

        ListaLocais* novoNo = (ListaLocais*)malloc(sizeof(ListaLocais));
        novoNo->local = local;
        novoNo->prox = NULL;
        novoNo->ant = NULL;

        if (*lista == NULL) {
            *lista = novoNo;
        } else {
            ListaLocais* ultimo = *lista;
            while (ultimo->prox != NULL) {
                ultimo = ultimo->prox;
            }
            novoNo->ant = ultimo;
            ultimo->prox = novoNo;
        }
    }

    fclose(arquivo);
}

// Função para ler e armazenar a lista de caminhos
void lerArquivoArestas(ListaArestas** listaAresta, const char* nomeArquivo, ListaLocais* listaLocais) {
    char linha[100];
    // Abre o arquivo de caminhos
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == '#') {
            // Ignora linhas que começam com #
            continue;
        }

        // Remove a quebra de linha (\n) do final da linha
        linha[strcspn(linha, "\n")] = '\0';

        // Aloca memória para a estrutura Arestas
        Arestas* novaAresta = (Arestas*)malloc(sizeof(Arestas));

        // Aloca memória e copia a origem
        novaAresta->origem = (char*)malloc(5 * sizeof(char));

        strncpy(novaAresta->origem, linha, 4);
        novaAresta->origem[4] = '\0';

        // Encontra a posição da vírgula
        char* virgula = strchr(linha, ',');

        // Aloca memória e copia o destino
        novaAresta->destino = (char*)malloc(5 * sizeof(char));

        strncpy(novaAresta->destino, virgula + 1, 4);
        novaAresta->destino[4] = '\0';

        // Inicializa a distância como 0
        novaAresta->distancia = 0.0;

        atualizarDistancia(novaAresta, listaLocais);

        // Cria um novo nó da lista
        ListaArestas* novoNo = (ListaArestas*)malloc(sizeof(ListaArestas));
        if (novoNo == NULL) {
            printf("Erro ao alocar memória.\n");
            free(novaAresta->origem);
            free(novaAresta->destino);
            free(novaAresta);
            fclose(arquivo);
            return;
        }

        // Define os valores do novo nó
        novoNo->aresta = novaAresta;
        novoNo->prox = NULL;
        novoNo->ant = NULL;

        // Insere o novo nó na lista
        if (*listaAresta == NULL) {
            // Se a lista estiver vazia, o novo nó será o primeiro e o último
            *listaAresta = novoNo;
        } else {
            // Caso contrário, insere o novo nó no final da lista
            ListaArestas* ultimo = *listaAresta;
            while (ultimo->prox != NULL) {
                ultimo = ultimo->prox;
            }
            ultimo->prox = novoNo;
            novoNo->ant = ultimo;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);
}

void atualizarDistancia(Arestas* aresta, ListaLocais* listaLocais) {
    ListaLocais* aux = listaLocais;
    double distanciaCalculada = 0.0;
    double lat1, lon1, lat2, lon2;
    lat1 = lon1 = lat2 = lon2 = 0.0;

    while (aux != NULL) {
        if (strcmp(aresta->origem, aux->local->nome) == 0) {
            lat1 = aux->local->latitude;
            lon1 = aux->local->longitude;
        }
        if (strcmp(aresta->destino, aux->local->nome) == 0) {
            lat2 = aux->local->latitude;
            lon2 = aux->local->longitude;
        }
        aux = aux->prox;
    }
    
    // Converter as coordenadas de graus para radianos
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;
    
    // Calcular a diferença entre as latitudes e longitudes
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    // Aplicar a fórmula de haversine
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distancia = R * c;
    
    distanciaCalculada += distancia * 1000.0; // Converter para metros
    
    aresta->distancia = distanciaCalculada;
}

