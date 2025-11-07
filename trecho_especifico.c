#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ler(char nomeArq[], int br, int trecho1, int trecho2){

FILE *arquivo=fopen(nomeArq, "r");
int campo1=0,campo4=0,controle=0;
float campo2=0;
char campo3='x',temp[4];

if(arquivo==NULL){printf("Erro, arquivo nao encontrado");return;}
fscanf(arquivo, "%*[^\n]\n");
while(!feof(arquivo)){
    fscanf(arquivo, "%d;%f;%c;%d", &campo1, &campo2, &campo3, &campo4);
    if(campo1==br){
        if(campo2>=trecho1 && campo2<=trecho2){
            FILE *avisos=fopen("alertas_por_br.csv","a");
            fprintf(avisos, "%d;%.1f;%c;%d\n", campo1, campo2, campo3, campo4);
            fclose(avisos);
            }
            }
}
fclose(arquivo);
}

void criararquivo(){

FILE *arquivo=fopen("alertas_por_br.csv", "w");

if (arquivo==NULL){printf("Erro ao criar arquivo");}
fprintf(arquivo, "br;km;tipoAlerta;upvotes\n");
}

int main(){
int br, trecho1, trecho2;
char nomearquivo[]="dadosConsolidados.csv";
printf("Digite a BR e o trecho especifico da br (Ex: 102 150 170)\n");
scanf("%d %d %d", &br, &trecho1, &trecho2);
criararquivo();
ler(nomearquivo, br, trecho1, trecho2);}
