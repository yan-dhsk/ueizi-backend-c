#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ler(char nomeArq[], int br, float trecho1, float trecho2){

FILE *arquivo=fopen(nomeArq, "r");
FILE *avisos=fopen("alertas_por_br.csv","w");

if(arquivo==NULL){printf("Erro, arquivo de dados nao encontrado");return;}
if(avisos==NULL){printf("Erro ao criar arquivos de alertas");return;}

int campo1=0,campo4=0;
float campo2=0.0;
char campo3='x';

fscanf(arquivo, "%*[^\n]\n");
fprintf(avisos, "br;km;tipoAlerta;upvotes \n");
while(fscanf(arquivo, " %d;%f;%c;%d%*c", &campo1, &campo2, &campo3, &campo4) == 4){
        if(campo1==br && campo2>=trecho1 && campo2<=trecho2){
            fprintf(avisos, "%d;%.1f;%c;%d\n", campo1, campo2, campo3, campo4);
            }
}
fclose(avisos);
fclose(arquivo);
}

