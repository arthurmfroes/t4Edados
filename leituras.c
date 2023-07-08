#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leituras.h"

#define TAM_MAX_LINHA 90

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
void lerListaCaminhos(ListaArestas** lista, const char* nomeArquivol, ListaLocais* listaLocais) {
    FILE* arquivo;
    char linha[100];

    // Abre o arquivo de caminhos
    arquivo = fopen("caminhos.txt", "r");
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
        if (*lista == NULL) {
            // Se a lista estiver vazia, o novo nó será o primeiro e o último
            *lista = novoNo;
        } else {
            // Caso contrário, insere o novo nó no final da lista
            ListaArestas* ultimo = *lista;
            while (ultimo->prox != NULL) {
                ultimo = ultimo->prox;
            }
            ultimo->prox = novoNo;
            novoNo->ant = ultimo;
        }
        atualizarDistancia(novoNo, listaLocais);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

void atualizarDistancia (ListaArestas** no, ListaLocais* listaLocais) {
    ListaLocais* aux = listaLocais;
    double distanciaCalculada = 0.0;
    while (aux != NULL) {
        if (strcmp((*no)->aresta->origem, aux->local->nome) == 0) {
            //inserir formula para calcular distancia utilizando hipotenusa
        }
        if (strcmp((*no)->aresta->destino, aux->local->nome) == 0) {
            //inserir formula para calcular distancia utilizando hipotenusa
        }
        aux = aux->prox;
    }
    (*no)->aresta->distancia = distanciaCalculada;
}