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

void determinaMenorCaminho(Grafo self, ListaLocais* listalocais) {
    char *linhaslidas[MAX_VISITAS];
    int visitas[MAX_VISITAS];
    int i;


    // Chame a função para ler o arquivo
    lerArquivoTexto("visita.csv", linhaslidas);

    criarVetorDeVisitas(linhaslidas, listalocais, visitas);

    for (i = 0; i < MAX_VISITAS; i++) {
        printf("%d\n", visitas[i]);
    }

}


