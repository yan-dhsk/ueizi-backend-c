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

void carregarArquivo(char nomeArquivo[]);
void carregarConsolidado(char nomeConsolidado[]);
void processarArquivo (Estrada **estradasPonteiro, Estrada *estradas, int br, float trechoDaBr, char tipo);
void compararArquivos (Estrada *estradas, Estrada *dados);
void salvarArquivo(Estrada *estrada, char nomeConsolidado[]);

void main(){
char nomeArquivo[] = "alertas_100000_1.csv";
char nomeConsolidade[] = "dadosConsolidados.csv";
carregarArquivo (nomeArquivo);
carregarConsolidado(nomeConsolidade);
}

void carregarArquivo (char nomeArquivo[]){
FILE* carregado = fopen(nomeArquivo, "r");
if (carregado == NULL){
    printf("Nao foi possivel abrir o arquivo");
    return;
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
            }
            copia2 = copia2->proximo;
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
if (*estradasPonteiro == NULL){controle++;}
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
    *estradasPonteiro = noBR;
    } else {
    copia->proximo = noBR;
    }
    return;
}
}

void carregarConsolidado(char nomeConsolidado[]){
FILE *consolidado = fopen(nomeConsolidado, "r");
if (consolidado == NULL) {
    printf("Nao existe arquivos anteriormente salvo\n");
    printf("Um novo arquivo sera criado\n");
    return;
}
Estrada *dados = NULL;
int controle = 0;
int br, upvotes;
float trecho;
char tipo;
Estrada *copia = dados;
while (fscanf(consolidado, "%d;%d;%c;%f", &br, &trecho, &tipo, &upvotes) == 4){
if (controle == 0){
    controle++;
    continue;
}
if (dados == NULL || copia->br != br){
Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
noBR->br = br;
noBR->proximo = NULL;
Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
noBR->inicioTrecho = noTrecho;
noTrecho->trechoDaBr = trecho;
}
copia = copia->proximo;
}
}

void salvarArquivo(Estrada *estrada, char nomeConsolidado[]){
FILE *salvo = fopen(nomeConsolidado, "w");
if (salvo == NULL){
    printf("Erro ao salvar arquivo");
    return;
}
Estrada *copia = estrada;
Trecho *copia2 = copia->inicioTrecho;
fprintf(salvo, "br;trecho;tipo;upvotes");
while (copia->inicioTrecho != NULL){
    fprintf(salvo, "%d;%d;%c;%d\n", copia->br, copia2->trechoDaBr, copia2->tipo, copia2->upvotes);
    copia2 = copia2->proximo;
    copia = copia->proximo;
}
printf("Arquivo salvo com sucesso!");
fclose(salvo);
}

