#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>

#include "../estruturas.h"

int lerValoresArquivo(FILE* fd, int** vetor,int quantidade){
	char linha[128];
	int valor;
	int contador=0;

	int maior=0;

	int *temp=realloc((*vetor),(quantidade)*sizeof(int));

	if(temp==NULL) return -1;

	while(fgets(linha,sizeof(linha),fd)!=NULL && contador<quantidade){
		valor=atoi(linha);

		temp[contador]=valor;

		if(valor>maior) maior=valor;

		contador++;
	}

	(*vetor)=temp;

	return maior;
}
int lerConfigsArquivo(FILE* fd,Configuracoes* configs, ConfigsRaylib* configs_tela){

	char linha[128];

	char* parametro;
	char* separador;
	char* valor;

	int contador=0;

	while(fgets(linha,sizeof(linha),fd)!=NULL){

		if(linha[0]=='\n' || linha[0]=='\r' || linha[0]=='\0') continue;

		separador=strchr(linha,'=');

		*separador='\0';

		parametro=linha;

		valor=separador+1;

		switch(contador){
			case 0:
				configs->teste=!strcmp(valor,"true\n");
				break;
			case 1:
				configs->quantidade_valores=atoi(valor);
				break;
			case 2:
				configs->ordenado=!strcmp(valor,"true\n");
				break;
			case 3:
				configs->crescente=!strcmp(valor,"true\n");
				break;
			case 4:
				strcpy(configs->arquivo_saida,valor);
				break;
			case 5:
				configs->visualizacao=(!strcmp(valor,"barras\n"))?BARRAS:ARVORE;
				break;
			case 6:
				configs_tela->largura=atoi(valor);
				break;
			case 7:
				configs_tela->altura=atoi(valor);
				break;
			case 8:
				configs_tela->fps=atof(valor);
				break;
			case 9:
				configs_tela->margem=atoi(valor);
				break;
			default:
				break;
		}
		contador++;
	}
	return 0;

}
int salvarEstatisticasArquivo(FILE* fd,Configuracoes configs, int comparacoes, double tempo){

	fprintf(fd,
			"Algoritmo: Busca Binaria\n"
			"Elementos: %d\n"
			"%s\n"
			"Comparacoes: %d\n"
			"Tempo: %f ms\n",
			configs.quantidade_valores,(configs.ordenado==1)?(configs.crescente==1)?"Crescente":"Decrescente":"Aleatorio",comparacoes, tempo*1000);

	return 0;
}
