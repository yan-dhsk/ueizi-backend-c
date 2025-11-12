#ifndef LOAD_FILES
#define LOAD_FILES

typedef struct Pedaco {
    float trechoDaBr;
    char tipo;
    int upvotes;
    struct Pedaco *proximo;
} Trecho;

typedef struct Rua {
    int br;
    Trecho *inicioTrecho;
    struct Rua *proximo;
} Estrada;

Estrada* carregarArquivo(char nomeArquivo[]);
Estrada* carregarConsolidado(char nomeConsolidado[]);
void processarArquivo (Estrada **estradasPonteiro, int br, float trechoDaBr, char tipo, int upvotesParaAdicionar);
void compararArquivos (Estrada **listaConsolidadaPonteiro, Estrada *listaNovosAlertas);
void salvarArquivo(Estrada *estrada, char nomeConsolidado[]);
void liberarLista(Estrada *lista);


#endif //LOAD_FILES
