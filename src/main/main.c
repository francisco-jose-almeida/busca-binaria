/*
	Esse programa tem o objetivo de receber uma lista ordenada de valores inteiros crescentes atravez de um arquivo e buscar um valor especifico utlizando busca binaria, tambem sera implementada uma visualizacao da busca em execucao.
	Adicionalmente ele deve medir as estatisticas necessarias ()
*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../visualizacoes/barras/barras.h"

#define WIDTH	800
#define HEIGHT	600


int lerValoresArquivo(FILE* fd, int** vetor,int* quantidade){
	
	char linha[128];
	int valor;
	
	int *temp=realloc((*vetor),((*quantidade)+1)*sizeof(int));
	
	if(temp==NULL) return 1;


	while(fgets(linha,sizeof(linha),fd)!=NULL){
		(*quantidade)++;
		valor=atoi(linha);
		
		temp[(*quantidade)-1]=valor;
	}

	(*vetor)=temp;

	return 0;
}


int main(){
	srand(time(NULL));

	SetTargetFPS(60);
	
	int quantidade_valores=0;

	int* valores=(int*) malloc(quantidade_valores*sizeof(int));

	FILE* valores_fd=fopen("valores.bin","rb");

	if(valores_fd==NULL) {
		return 1;
	}

	//Lendo valores do arquivo para o vetor
	lerValoresArquivo(valores_fd, &valores,&quantidade_valores);

	//Definindo alvo aleatoriamente
	int alvo=valores[rand()%quantidade_valores];

	//Iniciando janela raylib
	InitWindow(WIDTH,HEIGHT, "Algoritmo de Busca por Arvore Binaria");
	//Iniciando valores como Knuth
	int* K=valores;			//Vetor Ordenado
	int  k=alvo;			//Inteiro Alvo
	int  N=quantidade_valores-1;	//Numero de elementos do vetor

	int passo=0;

	//Indices inicial e final
	int l=0;
	int u=N;

	//Indice do ponto medio
	int i=(l+u)/2;		

	while(!WindowShouldClose()){

		if(k!=K[i]){
			if(u<l) {
				return 1;
			}
		
			passo++;
		
			//Calcular ponto medio
			i=(l+u)/2;		

			//Comparar
			if(k<K[i]){
				u=i;
			}
			else if(k>K[i]){
				l=i;
			}
		}

		desenharBarras(valores,quantidade_valores,l,u,i,alvo,passo);
	
	}

	CloseWindow();
	return 0;
}

