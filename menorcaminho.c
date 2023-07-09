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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void dijkstra(Grafo g, ListaLocais* lv, Vertice_Info info[]){
    int i, j;
    char *linhas_Visitadas[MAX_VISITAS];
    int vetor_visitas[MAX_VISITAS];

    lerArquivoTexto("visita.csv", linhas_Visitadas);

    printf("saiu do ler arquivo\n");

    for (int i = 0; i < MAX_VISITAS; i++) {
            ListaLocais *lista = lv;
            while (lista != NULL) {
                if (strcmp(lista->local->nome, linhas_Visitadas[i]) == 0) {
                    vetor_visitas[i] = lista->local->id;
                    printf("id: %d\n", vetor_visitas[i]);
                    break;
                } else {
                lista = lista->prox; }
            }
    }


    int num_vertices = g->nvertices;

    for(i = 0; i < num_vertices; i++){
        printf("Entrou no primeiro for");
        info[i].predecessor = -1;
        info[i].distancia = INT_MAX;
        info[i].visitado = 0;
    }

    int origem = vetor_visitas[0];
    info[origem].distancia = 0;

    for(i = 0; i < num_vertices; i++){
        printf("Entrou no segundo for");
        int menor_Dist = INT_MAX;
        int menor_Vertice = -1;

        for(j = 0; j < num_vertices; j++){
            if(!info[j].visitado && info[j].distancia < menor_Dist){
                menor_Dist = info[j].distancia;
                menor_Vertice = j;
            }
        }
        if(menor_Vertice == -1) break;

        info[menor_Vertice].visitado = 1;

        for(j = 0; j < num_vertices; j++){
            if(g->matriz_arestas[menor_Vertice][j] > 0){
                int alt = info[menor_Vertice].distancia + g->matriz_arestas[menor_Vertice][j];

                if(alt < info[j].distancia){
                    info[j].distancia = alt;
                    info[j].predecessor = menor_Vertice;
                }
            }
        }        
    }
    printf("Teste");
    for(i = 0; i < num_vertices; i++){
        printf("Vertice: %s, Distancia: %d\n", lv[i].local->nome, info[i].distancia);
    }
}  
