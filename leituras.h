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
    struct ListaArestas* prox;
    struct ListaArestas* ant;
} ListaArestas;

void lerArquivoVertices(ListaLocais** lista, const char* nomeArquivo);
void lerArquivoArestas(ListaArestas** lista, const char* nomeArquivol, ListaLocais* listaLocais);
void atualizarDistancia (ListaArestas** no, ListaLocais* listaLocais);

#endif  // LEITURAS_H
