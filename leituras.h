#ifndef LEITURAS_H
#define LEITURAS_H

typedef struct locais {
    int id;
    char* nome;
    double latitude;
    double longitude;
    char* desc;
} Locais;

typedef struct listalocais {
    Locais* local;
    struct ListaLocais* prox;
    struct ListaLocais* ant;
} ListaLocais;

typedef struct arestas {
    char* origem;
    char* destino;
    double distancia;
} Arestas;

typedef struct listaarestas {
    Arestas* aresta;
    struct listaarestas* prox;
    struct listaarestas* ant;
} ListaArestas;

void lerArquivoVertices(ListaLocais** listaLocais, const char* nomeArquivo);
void atualizarDistancia (ListaArestas** no, ListaLocais* listaLocais);
void lerArquivoArestas(ListaArestas** listaArestas, const char* nomeArquivo, ListaLocais* listaLocais);

#endif  // LEITURAS_H
