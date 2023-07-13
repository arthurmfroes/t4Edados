#include <stdio.h>
#include <stdlib.h>
#include "leituras.h"
#include "grafo.h"

int main() {
    listavertices lista_de_vertices = NULL;
    listaarestas lista_de_arestas = NULL;
    Grafo self = NULL;
    printf("criou variaveis");
    int num_vertices = carregaVertices(lista_de_vertices, "locais.csv"); //inicializa a lista de locais e armazena todo conteudo do arquivo nela, cria grafo com N locais
    self = g_cria(num_vertices, false);
    num_vertices = g_nvertices(self);
    printf("%d", num_vertices);
    printf("carregou vertices");
    lerArquivoArestas(lista_de_arestas, "caminhos.csv", lista_de_vertices); //inicializa a lista de arestas e armazena todo conteudo do arquivo nela
    printf("ler arquivo arestas");
    insereListasNoGrafo(self, lista_de_arestas); //insere as arestas no grafo
    printf("insere lista no grafo");

    //g_arestas(self);

}
