#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alertaTodasBr.h"
#include "trecho_especifico.h"
#include "load_files.h"

void main () {
while(1){
printf("===================Ola, bem-vindo ao sistema Uezi=====================\n");
printf("1 - Carregar e processar novos arquivos\n2 - Consultar trechos especificos\n3 - Organizar arquivos por BR's\n0 - Finalizar o programa\n");
printf("Porfavor, selecione sua opcao: ");
int escolha;
scanf("%d", &escolha);
switch (escolha){
case 1:
    printf("Porfavor, digite o nome (junto da extensao) do arquivo a ser carregado: ");
    char nomeArquivo[200];
    getchar();
    fgets(nomeArquivo, 200, stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
    char nomeConsolidado[] = "dadosConsolidados.csv";
    Estrada *listaConsolidada = carregarConsolidado(nomeConsolidado);
    Estrada *listaNovosAlertas = carregarArquivo(nomeArquivo);
    compararArquivos(&listaConsolidada, listaNovosAlertas);
    salvarArquivo(listaConsolidada, nomeConsolidado);
    liberarLista(listaConsolidada);
    liberarLista(listaNovosAlertas);
    break;
case 2:
    int br;
    float trecho1, trecho2;
    char nomearquivo[]="dadosConsolidados.csv";
    printf("Digite a BR e o trecho especifico da br (Ex: 102(BR) 150(Inicio do trecho) 170(final do trecho))\n");
    scanf("%d %f %f", &br, &trecho1, &trecho2);
    ler(nomearquivo, br, trecho1, trecho2);
    printf("Arquivo salvo com sucesso!\n");
    break;
case 3:
char nomeArquivos[]="dadosConsolidados.csv";
lerBrs(nomeArquivos);
printf("Arquivo salvo com sucesso!\n");
break;
case 0:
    printf("Encerrando programa...");
    return;
default:
    printf("Valor invladio!\n");
    break;
}}}
