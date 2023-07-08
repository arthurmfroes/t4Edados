#include <stdio.h>
#include <stdlib.h>
#include "leituras.h"

void imprimirLista(ListaLocais* lista) {
    ListaLocais* atual = lista;

    while (atual != NULL) {
        printf("ID: %d\n", atual->local->id);
        printf("Nome: %s\n", atual->local->nome);
        printf("Latitude: %lf\n", atual->local->latitude);
        printf("Longitude: %lf\n", atual->local->longitude);
        printf("Descrição: %s\n", atual->local->desc);
        printf("---------------------\n");

        atual = atual->prox;
    }
}

int main() {
    ListaLocais* lista = NULL;
    lerArquivo(&lista, "locais.csv"); //inicializa a lista de locais e armazena todo conteudo do arquivo nela
    imprimirLista(lista);

    // Liberar memória alocada para a lista de locais
    ListaLocais* atual = lista;
    while (atual != NULL) {
        ListaLocais* proximo = atual->prox;
        free(atual->local->nome);
        free(atual->local->desc);
        free(atual->local);
        free(atual);
        atual = proximo;
    }

    return 0;
}
