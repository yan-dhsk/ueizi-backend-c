#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tipagem(char tipo, int *upvotes, int numAlertas){

switch(tipo){

case 'A':upvotes[0]+=numAlertas;break;
case 'B':upvotes[1]+=numAlertas;break;
case 'C':upvotes[2]+=numAlertas;break;
case 'D':upvotes[3]+=numAlertas;break;
case 'E':upvotes[4]+=numAlertas;break;
case 'F':upvotes[5]+=numAlertas;break;}
}


void lerBrs(char nomeArquivo[]){

FILE *dados=fopen(nomeArquivo,"r");
FILE *alertas=fopen("alertas_br_todas.csv","w");

if(dados==NULL){printf("Erro, arquivo de dados nao encontrado");return;}
if(alertas==NULL){printf("Erro ao criar arquivos de alertas");return;}

int br=1, brAnterior=0, numAlertas=0, numAlertasAnteriores=0, upvotes[]={0,0,0,0,0,0,65,66,67,68,69,70};
char tipo, tipoAnterior;

fscanf(dados, "%*[^\n]\n");
fprintf(alertas, "br;tipoAlerta;quantidade\n");

while(fscanf(dados, "%d;%*f;%c;%d\n", &br, &tipo, &numAlertas)==3){ printf("%d - %c - %d  ;  ", br, tipo, numAlertas);
    if(br==brAnterior){
        tipagem(tipoAnterior, upvotes,numAlertasAnteriores);}
    else if(br!=0){
        tipagem(tipoAnterior, upvotes,numAlertasAnteriores);
        for(int x=0;x<6;x++){
            fprintf(alertas, "%d,%c,%d\n", brAnterior, upvotes[x+6], upvotes[x]);}
        int upvotes[]={0,0,0,0,0,0,65,66,67,68,69,70};
    }

    brAnterior=br;
    tipoAnterior=tipo;
    numAlertasAnteriores=numAlertas;}

tipagem(tipoAnterior, upvotes,numAlertasAnteriores);
for(int x=0;x<6;x++){
    fprintf(alertas, "%d,%c,%d\n", brAnterior, upvotes[x+6], upvotes[x]);}

fclose(dados);
fclose(alertas);
}



int main(){

char nomeArquivo[]="dadosConsolidados.csv";

lerBrs(nomeArquivo);
}
