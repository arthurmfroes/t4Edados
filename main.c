#include <stdio.h>
#include <stdlib.h>
#include "leituras.h"
#include "grafo.h"
#include "menorcaminho.h"

int main() {
    listavertices lista_de_vertices = NULL;
    listaarestas lista_de_arestas = NULL;
    Grafo self = NULL;

    lista_de_vertices = carregaVertices(lista_de_vertices, "locais.csv"); //inicializa a lista de locais e armazena todo conteudo do arquivo nela, retorna a quantidade de vertices

    int num_vertices = retornaNumVertices(lista_de_vertices);
    self = g_cria(num_vertices, false);

    lista_de_arestas = lerArquivoArestas(lista_de_arestas, "caminhos.csv", lista_de_vertices); //inicializa a lista de arestas e armazena todo conteudo do arquivo nela

    insereListasNoGrafo(self, lista_de_arestas); //insere as arestas no grafo

    EncontraMenorCaminho(self, lista_de_vertices);

    g_destroi(self);
    free(lista_de_vertices);
    free(lista_de_arestas);

}
