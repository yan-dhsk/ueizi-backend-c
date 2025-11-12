#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

Estrada* carregarArquivo (char nomeArquivo[]){
    FILE* carregado = fopen(nomeArquivo, "r");
    if (carregado == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        return NULL;
    }
    int lixo1, lixo2, br;
    float trechoDaBr;
    char tipo;
    char lixoBuffer[256];
    if (fgets(lixoBuffer, sizeof(lixoBuffer), carregado) == NULL) {
        printf("Erro ao ler o cabeçalho do arquivo ou arquivo vazio.\n");
        fclose(carregado);
        return NULL;
    }
    Estrada *estradas = NULL;
    while (fscanf (carregado, "%d;%d;%d;%f;%c", &lixo1, &lixo2, &br, &trechoDaBr, &tipo) == 5){
        float parteInteira = floorf(trechoDaBr);
        float parteFracionaria = trechoDaBr - parteInteira;
        if (parteFracionaria < 0.5) {
            trechoDaBr = parteInteira;
        } else {
            trechoDaBr = parteInteira + 0.5;
        }
        processarArquivo(&estradas, br, trechoDaBr, tipo, 1);
    }
    fclose(carregado);
    return estradas;
}

void processarArquivo (Estrada **estradasPonteiro, int br, float trechoDaBr, char tipo, int upvotesParaAdicionar) {
    Estrada *copia = *estradasPonteiro;
    Estrada *ultimoNoBR = NULL;
    while (copia != NULL) {
        if (br == copia->br) {
            Trecho *copia2 = copia->inicioTrecho;
            Trecho *copia3 = NULL;
            while (copia2 != NULL) {
                if (trechoDaBr == copia2->trechoDaBr && tipo == copia2->tipo) {
                    copia2->upvotes += upvotesParaAdicionar;
                    return;
                }
                copia3 = copia2;
                copia2 = copia2->proximo;
            }
            Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
            if (!noTrecho) { printf("Erro de alocacao (Trecho)\n"); return; }
            noTrecho->tipo = tipo;
            noTrecho->trechoDaBr = trechoDaBr;
            noTrecho->upvotes = upvotesParaAdicionar;
            noTrecho->proximo = NULL;
            copia3->proximo = noTrecho;
            return;
        }
        ultimoNoBR = copia;
        copia = copia->proximo;
    }

    Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
    if (noBR == NULL) {
        printf("Erro de alocação (Estrada)");
        return;
    }
    noBR->br = br;
    noBR->proximo = NULL;

    Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
    if (noTrecho == NULL) {
        printf("Erro de alocação (Trecho)");
        free(noBR);
        return;
    }
    noBR->inicioTrecho = noTrecho;
    noTrecho->tipo = tipo;
    noTrecho->trechoDaBr = trechoDaBr;
    noTrecho->upvotes = upvotesParaAdicionar;
    noTrecho->proximo = NULL;

    if (*estradasPonteiro == NULL) {
        *estradasPonteiro = noBR;
    } else {
        ultimoNoBR->proximo = noBR;
    }
    return;
}


Estrada* carregarConsolidado(char nomeConsolidado[]){
    FILE *consolidado = fopen(nomeConsolidado, "r");
    if (consolidado == NULL) {
        printf("Nao existe arquivos anteriormente salvo\n");
        printf("Um novo arquivo sera criado\n");
        return NULL;
    }
    Estrada *dados = NULL;
    int br, upvotes;
    float trecho;
    char tipo;
    Estrada *copia = NULL;
    char lixoBuffer[256];
    if (fgets(lixoBuffer, sizeof(lixoBuffer), consolidado) == NULL) {
        printf("Erro ao ler o cabeçalho do arquivo consolidado ou arquivo vazio.\n");
        fclose(consolidado);
        return NULL;
    }

    while (fscanf(consolidado, "%d;%f;%c;%d", &br, &trecho, &tipo, &upvotes) == 4){
        int brEncontrada = 0;

        if (dados == NULL) {
            Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
            noBR->br = br;
            noBR->proximo = NULL;
            Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
            noBR->inicioTrecho = noTrecho;
            noTrecho->trechoDaBr = trecho;
            noTrecho->tipo = tipo;
            noTrecho->upvotes = upvotes;
            noTrecho->proximo = NULL;
            dados = noBR;
        } else {
            copia = dados;
            Estrada *ultimoNoBR = dados;

            while (copia != NULL) {
                if (copia->br == br) {
                    Trecho *trecho2 = copia->inicioTrecho;
                    while (trecho2->proximo != NULL) {
                        trecho2 = trecho2->proximo;
                    }
                    Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
                    noTrecho->trechoDaBr = trecho;
                    noTrecho->tipo = tipo;
                    noTrecho->upvotes = upvotes;
                    noTrecho->proximo = NULL;
                    trecho2->proximo = noTrecho;
                    brEncontrada = 1;
                    break;
                }
                ultimoNoBR = copia;
                copia = copia->proximo;
            }

            if (brEncontrada == 0) {
                Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
                noBR->br = br;
                noBR->proximo = NULL;
                Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
                noBR->inicioTrecho = noTrecho;
                noTrecho->trechoDaBr = trecho;
                noTrecho->tipo = tipo;
                noTrecho->upvotes = upvotes;
                noTrecho->proximo = NULL;
                ultimoNoBR->proximo = noBR;
            }
        }
    }
    fclose(consolidado);
    return dados;
}

void salvarArquivo(Estrada *estrada, char nomeConsolidado[]){
    FILE *salvo = fopen(nomeConsolidado, "w");
    if (salvo == NULL){
        printf("Erro ao salvar arquivo");
        return;
    }
    Estrada *copia = estrada;
    fprintf(salvo, "br;trecho;tipo;upvotes\n");
    while (copia != NULL) {
        Trecho *copia2 = copia->inicioTrecho;
        while (copia2 != NULL) {
            fprintf(salvo, "%d;%.1f;%c;%d\n", copia->br, copia2->trechoDaBr, copia2->tipo, copia2->upvotes);
            copia2 = copia2->proximo;
        }
        copia = copia->proximo;
    }
    printf("Arquivo salvo com sucesso!\n");
    fclose(salvo);
}

void compararArquivos (Estrada **listaConsolidadaPonteiro, Estrada *listaNovosAlertas) {
    Estrada *brNova = listaNovosAlertas;
    while (brNova != NULL) {
        Trecho *trechoNovo = brNova->inicioTrecho;
        while (trechoNovo != NULL) {
            processarArquivo(listaConsolidadaPonteiro,
                             brNova->br,
                             trechoNovo->trechoDaBr,
                             trechoNovo->tipo,
                             trechoNovo->upvotes);
            trechoNovo = trechoNovo->proximo;
        }
        brNova = brNova->proximo;
    }
}

void liberarLista(Estrada *lista) {
    Estrada *brAtual = lista;
    Estrada *tempBR;
    Trecho *trechoAtual;
    Trecho *tempTrecho;
    while (brAtual != NULL) {
        trechoAtual = brAtual->inicioTrecho;
        while (trechoAtual != NULL) {
            tempTrecho = trechoAtual;
            trechoAtual = trechoAtual->proximo;
            free(tempTrecho);
        }
        tempBR = brAtual;
        brAtual = brAtual->proximo;
        free(tempBR);
    }
}
