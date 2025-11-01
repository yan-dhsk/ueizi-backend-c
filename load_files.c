#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedaço {
int trechoDaBr;
char tipo;
int upvotes = 0;
struct Pedaço *proximo = NULL;
} Trecho;

typedef struct Rua {
int br;
Trecho *inicioTrecho = NULL;
struct Rua *proximo = NULL;
} Estrada;

void carregarArquivo(char nomeArquivo[]);
void processarArquivo (Estrada **estradasPonteiro, *estradas int br, int trechoDaBr, char tipo);
void salvarArquivo ();

void main {
char nomeArquivo[] = "alertas_100000_1.csv"
carregarArquivo (nomeArquivo);
}

void carregarArquivo (char nomeArquivo[]){
FILE* carregado = fopen(nomeArquivo, "r");
int lixo1, lixo2, br, trechoDaBr;
char tipo;
int controle = 0;
Estrada *estradas = NULL;
while (fscanf (carregado, "%d;%d;%d;%d;%c", &lixo1, &lixo2, &br, &trechoDaBr, &tipo) != NULL){
    if (controle == 0) {
        controle++;
        continue;
    }
    processarArquivo(*estradas, estradas, br, trechoDaBr, tipo);
}
controle = 0;
}

void processarArquivo (Estrada **estradasPonteiro, *estradas int br, int trechoDaBr, char tipo) {
int controle = 0;
Estrada *copia = estradas;
Trecho *copia2 = copia->inicioTrecho;
while (*copia != NULL){
    if (br == copia->br){
        while(*copia2 != NULL){
            if (trechoDaBr == copia2->trechoDaBr){
                copia2->upvotes++;
                break;
            copia2 = copia2->proximo;
            }
        if (copia2 == NULL){
            Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
            copia2->proximo = noTrecho;
            noTrecho->tipo = tipo;
            noTrecho->trechoDaBr = trechoDaBr;
            noTrecho->upvotes++;
        }
        }
    }
    copia = copia->proximo;
    }
if (copia->proximo == NULL || *estradasPonteiro == NULL){controle++;}
else if (copia->proximo == NULL || *estradasPonteiro != NULL){controle = 2;}
if (controle != 0) {
    Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
    noBR->br = br;
    Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
    noBR->inicioTrecho = noTrecho;
    noTrecho->tipo = tipo;
    noTrecho->trechoDaBr = trechoDaBr;
    noTrecho->upvotes++;
    if (controle == 1){
    estradas = noBR;
    } else {
    copia->proximo = noBR;
    }
    return;
}
}
