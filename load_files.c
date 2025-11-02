#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Pedaco {
int trechoDaBr;
char tipo;
int upvotes;
struct Pedaco *proximo;
} Trecho;

typedef struct Rua {
int br;
Trecho *inicioTrecho;
struct Rua *proximo;
} Estrada;

void carregarArquivo(char nomeArquivo[]);
void processarArquivo (Estrada **estradasPonteiro, Estrada *estradas, int br, float trechoDaBr, char tipo);
void salvarArquivo(void);

void main(){
char nomeArquivo[] = "alertas_100000_1.csv";
carregarArquivo (nomeArquivo);
}

void carregarArquivo (char nomeArquivo[]){
FILE* carregado = fopen(nomeArquivo, "r");
int lixo1, lixo2, br, trechoDaBr;
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
    processarArquivo(&estradas, estradas, br, trechoDaBr, tipo);
}
controle = 0;
fclose(carregado);
}

void processarArquivo (Estrada **estradasPonteiro, Estrada *estradas, int br, float trechoDaBr, char tipo) {
int controle = 0;
Estrada *copia = estradas;
Trecho *copia2 = copia->inicioTrecho;
while (copia != NULL){
    if (br == copia->br){
        while(copia2 != NULL){
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
            noTrecho->upvotes = 1;
            noTrecho->proximo = NULL;
        }
        }
    }
    copia = copia->proximo;
    copia2 = copia->inicioTrecho;
    }
if (copia->proximo == NULL || *estradasPonteiro == NULL){controle++;}
else if (copia->proximo == NULL || *estradasPonteiro != NULL){controle = 2;}
if (controle != 0) {
    Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
    noBR->br = br;
    noBR->proximo = NULL;
    Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
    noBR->inicioTrecho = noTrecho;
    noTrecho->tipo = tipo;
    noTrecho->trechoDaBr = trechoDaBr;
    noTrecho->upvotes = 1;
    if (controle == 1){
    estradas = noBR;
    } else {
    copia->proximo = noBR;
    }
    return;
}
}


