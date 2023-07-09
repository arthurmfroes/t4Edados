#ifndef MENORCAMINHO_H
#define MENORCAMINHO_H

#define MAX_VISITAS 10 // Número máximo de linhas

#include "grafo.h"
#include "leituras.h"

void lerArquivoTexto(const char *nomeArquivo, char **linhas);
void criarVetorDeVisitas(char **linhas, ListaLocais *listalocais, int visitas[MAX_VISITAS]);
void determinaMenorCaminho(Grafo self, ListaLocais* listalocais);
void dijkstra(Grafo grafo, int origem, int destino);


#endif