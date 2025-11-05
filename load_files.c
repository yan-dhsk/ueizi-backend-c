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
void processarArquivo (Estrada **estradasPonteiro, int br, float trechoDaBr, char tipo);
void compararArquivos (Estrada *estradas, Estrada *dados);
void salvarArquivo(Estrada *estrada, char nomeConsolidado[]);

void main(){
    char nomeArquivo[] = "alertas_100000_1.csv";
    char nomeConsolidado[] = "dadosConsolidados.csv";
    carregarArquivo (nomeArquivo);
    carregarConsolidado(nomeConsolidado);
}

Estrada* carregarArquivo (char nomeArquivo[]){
    FILE* carregado = fopen(nomeArquivo, "r");
    if (carregado == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return NULL;
    }
    int lixo1, lixo2, br;
    float trechoDaBr;
    char tipo;
    int controle = 0;
    Estrada *estradas = NULL;
    while (fscanf (carregado, "%d;%d;%d;%f;%c", &lixo1, &lixo2, &br, &trechoDaBr, &tipo) == 5){
        if (controle == 0) {
            controle++;
            continue;
        }
        float parteInteira = floorf(trechoDaBr);
        float parteFracionaria = trechoDaBr - parteInteira;
        if (parteFracionaria < 0.5) {
            trechoDaBr = parteInteira;
        } else {
            trechoDaBr = parteInteira + 0.5;
        }
        processarArquivo(&estradas, br, trechoDaBr, tipo);
    }
    fclose(carregado);
    return estradas;
}

void processarArquivo (Estrada **estradasPonteiro, int br, float trechoDaBr, char tipo) {
    Estrada *copia = *estradasPonteiro;
    Estrada *ultimoNoBR = NULL;

    while (copia != NULL) {
        if (br == copia->br) {
            Trecho *copia2 = copia->inicioTrecho;
            Trecho *copia3 = NULL;

            if (copia2 == NULL) {
                Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
                noTrecho->tipo = tipo;
                noTrecho->trechoDaBr = trechoDaBr;
                noTrecho->upvotes = 1;
                noTrecho->proximo = NULL;
                copia->inicioTrecho = noTrecho;
                return;
            }

            while (copia2 != NULL) {
                if (trechoDaBr == copia2->trechoDaBr) {
                    copia2->upvotes++;
                    return;
                }
                copia3 = copia2;
                copia2 = copia2->proximo;
            }

            Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
            noTrecho->tipo = tipo;
            noTrecho->trechoDaBr = trechoDaBr;
            noTrecho->upvotes = 1;
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
    noTrecho->upvotes = 1;
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
    int controle = 0;
    int br, upvotes;
    float trecho;
    char tipo;
    Estrada *copia = NULL;

    while (fscanf(consolidado, "%d;%f;%c;%d", &br, &trecho, &tipo, &upvotes) == 4){
        if (controle == 0){
            controle++;
            continue;
        }

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
            fprintf(salvo, "%d;%f;%c;%d\n", copia->br, copia2->trechoDaBr, copia2->tipo, copia2->upvotes);
            copia2 = copia2->proximo;
        }
        copia = copia->proximo;
    }
    printf("Arquivo salvo com sucesso!");
    fclose(salvo);
}
